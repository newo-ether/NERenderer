// infinitearealight.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <assert.h>
#include <malloc.h>

#include "infinitearealight.h"
#include "../image/image.h"
#include "../base/light.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/sampler.h"
#include "../base/utils.h"

Light InfiniteAreaLightInit(Image *spectrumLUT) {
    InfiniteAreaLightData *data;
    data = (InfiniteAreaLightData *)malloc(sizeof(InfiniteAreaLightData));
    data->spectrumLUT = spectrumLUT;

    Light light;
    light.lightData = (void *)data;
    light.type = InfiniteArea;
    light.GetLightSample = &InfiniteAreaLightGetLightSample;
    light.GetSpectrum = &InfiniteAreaLightGetSpectrum;
    light.GetSpectrumByDir = &InfiniteAreaLightGetSpectrumByDir;
    light.LightFree = &InfiniteAreaLightFree;
    return light;
}

Light * InfiniteAreaLightNew(Image *spectrumLUT) {
    InfiniteAreaLightData *data;
    data = (InfiniteAreaLightData *)malloc(sizeof(InfiniteAreaLightData));
    data->spectrumLUT = spectrumLUT;

    Light *light;
    light = (Light *)malloc(sizeof(Light));
    light->lightData = (void *)data;
    light->type = InfiniteArea;
    light->GetLightSample = &InfiniteAreaLightGetLightSample;
    light->GetSpectrum = &InfiniteAreaLightGetSpectrum;
    light->GetSpectrumByDir = &InfiniteAreaLightGetSpectrumByDir;
    light->LightFree = &InfiniteAreaLightFree;
    return light;
}

void InfiniteAreaLightFree(Light *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->lightData != NULL) {
        ImageFree(((InfiniteAreaLightData *)(this->lightData))->spectrumLUT, true);
        free(this->lightData);
    }
    if (freeThis) {
        free(this);
    }
}

Spectrum InfiniteAreaLightGetLightSample(Light *this, Point3 *p, double *pdf, Sampler *sampler) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return SpectrumInit(0, 0, 0);
    }
#endif
    Vector3 v;
    v = SamplerGenerateRandomSphereDir(sampler, pdf);
    *p = Vector3Mul(v, 10000);
    return InfiniteAreaLightGetSpectrumByDir(this, v);
}

// Note: This function won't be called if the program runs correctly.
Spectrum InfiniteAreaLightGetSpectrum(Light *this) {
    assert(false);
    return SpectrumInit(0, 0, 0);
}

Spectrum InfiniteAreaLightGetSpectrumByDir(Light *this, Vector3 dir) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return SpectrumInit(0, 0, 0);
    }
#endif
    InfiniteAreaLightData *data;
    Image *spectrumLUT;
    float *LUT, *pixel;
    double theta, cosTheta, sinTheta, invSinTheta, phi, x, y;
    int width, height, i, j;

    data = (InfiniteAreaLightData *)(this->lightData);
    spectrumLUT = data->spectrumLUT;

    if (ImageGetImageType(spectrumLUT) != HDR || ImageGetChannel(spectrumLUT) != RGB) {
        assert(false);
        return SpectrumInit(0, 0, 0);
    }

    width = ImageGetWidth(spectrumLUT);
    height = ImageGetHeight(spectrumLUT);
    LUT = ImageGetArray(spectrumLUT);

    Vector3DoNormalize(&dir);
    cosTheta = CLAMP(dir.z, -1, 1);
    sinTheta = sqrt(MAX(0, 1 - cosTheta * cosTheta));
    invSinTheta = 1 / sinTheta;
    theta = acos(cosTheta);
    x = acos(dir.x * invSinTheta);
    y = asin(dir.y * invSinTheta);
    phi = ArcTan2(y, x);
    i = CLAMP((int)(phi / (2 * PI) * width), 0, width - 1);
    j = CLAMP((int)(theta / PI * height), 0, height - 1);

    pixel = (float *)((char *)LUT + (j * width + i) * 3 * sizeof(float));
    return SpectrumInit(pixel[0], pixel[1], pixel[2]);
}
