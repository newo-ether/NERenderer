// pathtracer.c

#include "../config/config.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "pathtracer.h"
#include "../base/renderer.h"
#include "../base/sampler.h"
#include "../base/spectrum.h"
#include "../image/image.h"
#include "../base/scene.h"
#include "../base/object.h"
#include "../base/light.h"
#include "../base/camera.h"
#include "../base/list.h"
#include "../base/utils.h"

static Spectrum RecursivePathTracing(Renderer *this, Ray ray, Sampler *sampler, int depth);

Renderer PathTracerInit(Scene *scene, int samplePerPixel, int maxDepth, double russianRoulette) {
    PathTracerConfig *config;
    config = (PathTracerConfig *)malloc(sizeof(PathTracerConfig));
    config->samplePerPixel = samplePerPixel;
    config->maxDepth = maxDepth;
    config->russianRoulette = russianRoulette;

    Renderer renderer;
    renderer.rendererConfig = config;
    renderer.scene = scene;
    renderer.Render = &PathTracerRender;
    renderer.RendererFree = &PathTracerFree;

    return renderer;
}

Renderer * PathTracerNew(Scene *scene, int samplePerPixel, int maxDepth, double russianRoulette) {
    PathTracerConfig *config;
    config = (PathTracerConfig *)malloc(sizeof(PathTracerConfig));
    config->samplePerPixel = samplePerPixel;
    config->maxDepth = maxDepth;
    config->russianRoulette = russianRoulette;

    Renderer *renderer;
    renderer = (Renderer *)malloc(sizeof(Renderer));
    renderer->rendererConfig = config;
    renderer->scene = scene;
    renderer->Render = &PathTracerRender;
    renderer->RendererFree = &PathTracerFree;

    return renderer;
}

void PathTracerFree(Renderer *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->rendererConfig != NULL) {
        free(this->rendererConfig);
    }
    if (this->scene != NULL) {
        SceneFree(this->scene, true);
    }
    if (freeThis) {
        free(this);
    }
}

Image * PathTracerRender(Renderer *this) {
    PathTracerConfig *config;
    Image *image;
    Camera *camera;
    Sampler *sampler;
    int i, j;
    int width, height;
    int spp;
    uint8 *pixel;

#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return NULL;
    }
#endif

    // Get basic values.
    camera = this->scene->camera;
    config = (PathTracerConfig *)(this->rendererConfig);
    spp = config->samplePerPixel;

    // Initialize the image.
    width = CameraGetScreenWidth(camera);
    height = CameraGetScreenHeight(camera);
    image = ImageNew(width, height, RGB, LDR);
    sampler = SamplerNew(0);

    // Render the image.
    ImageForeachPixel(image, &i, &j, pixel, uint8) {
        Spectrum spectrum;
        spectrum = SpectrumInit(0, 0, 0);
        printf("\rRendering pixel [%4d,%4d] (%d%%)...", i, j, (j * width + i) * 100 / (width * height));
        for (int n = 0; n < spp; n++) {
            Ray ray = camera->GenerateSample(camera, i, j, sampler);
            SpectrumDoAdd(&spectrum, RecursivePathTracing(this, ray, sampler, 0));
        }
        SpectrumDoDiv(&spectrum, spp);
        pixel[0] = (uint8)(256 * CLAMP(pow(SpectrumGetR(&spectrum), 1 / 2.2), 0, 1));
        pixel[1] = (uint8)(256 * CLAMP(pow(SpectrumGetG(&spectrum), 1 / 2.2), 0, 1));
        pixel[2] = (uint8)(256 * CLAMP(pow(SpectrumGetB(&spectrum), 1 / 2.2), 0, 1));
    }

    return image;
}

static Spectrum RecursivePathTracing(Renderer *this, Ray ray, Sampler *sampler, int depth) {
    PathTracerConfig *config;
    List *objects;
    List *lights;
    Light *light;
    int maxDepth;
    double rr;

    // Get maxDepth and russianRoulette from the PathTracerConfig data.
    config = (PathTracerConfig *)(this->rendererConfig);
    maxDepth = config->maxDepth;
    rr = config->russianRoulette;

    // End the iteration if it satisfies the terminal condition.
    if (depth == maxDepth || SamplerGenerateRandom(sampler) > rr) {
        return SpectrumInit(0, 0, 0);
    }

    // Get objects and lights.
    objects = this->scene->objects;
    lights = this->scene->lights;

    // Check intersection with objects in the list.
    IntersectInfo isect;
    if (ObjectIntersect(objects, ray, &isect)) {
        // Add each Light's contribution.
        Material *material = isect.hitObj->material;
        Spectrum spectrum = SpectrumInit(0, 0, 0);
        ListForeachContent(lights, light, Light) {
            Point3 p;
            double pdf;
            Spectrum s = light->GetLightSample(light, &p, &pdf, sampler);
            Ray r = RayInit(isect.hitPoint, Point3Minus(p, isect.hitPoint), 0, 0.999);
            if (ObjectIsIntersect(objects, r)) {
                SpectrumDoDiv(&s, pdf);
                s = SpectrumMul(
                        SpectrumMix(s, material->BSDF(material, r.dir, isect.incomeDir, isect.hitNormal)),
                        Vector3Dot(r.dir, isect.hitNormal));

                SpectrumDoAdd(&spectrum, s);
            }
        }

        // Add Emissive Surface's contribution.
        Light *hitLight = isect.hitObj->light;
        if (light != NULL) {
            SpectrumDoAdd(&spectrum, hitLight->GetSpectrum(hitLight));
        }

        // Prepare for the next iteration.
        double pdf;
        Vector3 randDir;
        Spectrum Li, Lo;
        randDir = SamplerGenerateRandomHemisphereDir(sampler, isect.hitNormal, &pdf);
        Li = SpectrumDiv(
                RecursivePathTracing(this, RayInit(isect.hitPoint, randDir, 0, INFINITY), sampler, depth + 1),
                pdf);

        Lo = SpectrumMul(
                SpectrumMix(Li, material->BSDF(material, randDir, isect.incomeDir, isect.hitNormal)),
                Vector3Dot(randDir, isect.hitNormal));

        return SpectrumDiv(SpectrumAdd(spectrum, Lo), rr);
    }
    else {
        // Add Infinite Area Light(s)' contribution if no intersection point was found.
        Spectrum spectrum = SpectrumInit(0, 0, 0);
        ListForeachContent(lights, light, Light) {
            if (light->type == InfiniteArea) {
                SpectrumDoAdd(&spectrum, light->GetSpectrumByDir(light, ray.dir));
            }
        }
        return spectrum;
    }
}
