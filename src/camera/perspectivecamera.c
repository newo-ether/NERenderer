// perspectivecamera.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "perspectivecamera.h"
#include "../base/camera.h"
#include "../base/sampler.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/transform.h"
#include "../base/utils.h"
#include "../base/ray.h"

Camera PerspectiveCameraInit(Point3 pos,
                             Point3 look,
                             Vector3 up,
                             int screenWidth, 
                             int screenHeight, 
                             double fov, 
                             double near, 
                             double far,
                             double focalLength,
                             double lenRadius) {
    Camera camera;
    PerspectiveCameraData *data;
    data = (PerspectiveCameraData *)malloc(sizeof(PerspectiveCameraData));

    data->cam2ndc = TransformGeneratePerspective(fov, near, far);
    data->ndc2cam = TransformInverse(data->cam2ndc);
    data->fov = fov;
    data->near = near;
    data->far = far;
    data->focalLength = focalLength;
    data->lenRadius = lenRadius;

    camera.cameraData = (void *)data;
    camera.cam2world = TransformGenerateLookAt(pos, look, up);
    camera.world2cam = TransformInverse(camera.cam2world);
    camera.screenWidth = screenWidth;
    camera.screenHeight = screenHeight;
    camera.GenerateSample = &PerspectiveCameraGenerateSample;
    camera.CameraFree = &PerspectiveCameraFree;

    return camera;
}

Camera * PerspectiveCameraNew(Point3 pos,
                              Point3 look,
                              Vector3 up,
                              int screenWidth, 
                              int screenHeight, 
                              double fov, 
                              double near, 
                              double far,
                              double focalLength,
                              double lenRadius) {
    Camera *camera;
    PerspectiveCameraData *data;
    camera = (Camera *)malloc(sizeof(Camera));
    data = (PerspectiveCameraData *)malloc(sizeof(PerspectiveCameraData));

    data->cam2ndc = TransformGeneratePerspective(fov, near, far);
    data->ndc2cam = TransformInverse(data->cam2ndc);
    data->fov = fov;
    data->near = near;
    data->far = far;
    data->focalLength = focalLength;
    data->lenRadius = lenRadius;

    camera->cameraData = (void *)data;
    camera->cam2world = TransformGenerateLookAt(pos, look, up);
    camera->world2cam = TransformInverse(camera->cam2world);
    camera->screenWidth = screenWidth;
    camera->screenHeight = screenHeight;
    camera->GenerateSample = &PerspectiveCameraGenerateSample;
    camera->CameraFree = &PerspectiveCameraFree;

    return camera;
}

void PerspectiveCameraFree(Camera *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->cameraData != NULL) {
        free(this->cameraData);
    }
    if (freeThis) {
        free(this);
    }
}

Ray PerspectiveCameraGenerateSample(Camera *this, int x, int y, Sampler *sampler) {
    double screenWidth, screenHeight;
    double near, far, focalLength, lenRadius;
    double r, theta;
    PerspectiveCameraData *data;
    Transform cam2world, ndc2cam;
    Point3 pSample, sample, lenSample;
    Vector3 dir;
    Ray ray;

#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return RayInit(Point3Init(0, 0, 0), Vector3Init(0, 0, 0), 0, 0);
    }
#endif

    // Get values from the cameraData.
    data = (PerspectiveCameraData *)(this->cameraData);
    ndc2cam = data->ndc2cam;
    near = data->near;
    far = data->far;
    focalLength = data->focalLength;
    lenRadius = data->lenRadius;

    // Get values from this pointer.
    screenWidth = this->screenWidth;
    screenHeight = this->screenHeight;
    cam2world = this->cam2world;

    // Generate a sample point in the NDC space on the desired pixel described by x and y indicies.
    sample = Point3Init(SamplerGenerateRandom(sampler), SamplerGenerateRandom(sampler), 0);
    pSample = Point3Init((double)x - (double)screenWidth * 0.5 + sample.x,
                        -(double)y + (double)screenHeight * 0.5 - 1 + sample.y, 0);
    Vector3DoDiv(&pSample, (double)screenWidth * 0.5);
    TransformDoPoint3(ndc2cam, &pSample);

    // Generate a sample point in the camera space on the len for the depth of field.
    r = sqrt(SamplerGenerateRandom(sampler)) * lenRadius;
    theta = SamplerGenerateRandom(sampler) * 2 * PI;
    lenSample = Point3Init(r * cos(theta), r * sin(theta), 0);
    dir = Vector3Normalize(Point3Minus(Vector3Mul(pSample, focalLength / -pSample.z), lenSample));
    ray = RayInit(lenSample,
                  dir,
                  near / -dir.z,
                  far / -dir.z);

    // Transform the ray from the camera space to the world space.
    TransformDoRay(cam2world, &ray);

    return ray;
}
