// pointlight.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>

#include "pointlight.h"
#include "../base/light.h"
#include "../base/spectrum.h"
#include "../base/sampler.h"
#include "../base/point3.h"
#include "../base/vector3.h"

Light PointLightInit(Point3 pos, Spectrum spectrum) {
    PointLightData *data;
    data = (PointLightData *)malloc(sizeof(PointLightData));
    data->pos = pos;
    data->spectrum = spectrum;

    Light light;
    light.lightData = (void *)data;
    light.type = DeltaPosition;
    light.GetLightSample = &PointLightGetLightSample;
    light.GetSpectrum = &PointLightGetSpectrum;
    light.GetSpectrumByDir = &PointLightGetSpectrumByDir;
    light.LightFree = &PointLightFree;
    return light;
}

Light * PointLightNew(Point3 pos, Spectrum spectrum) {
    PointLightData *data;
    data = (PointLightData *)malloc(sizeof(PointLightData));
    data->pos = pos;
    data->spectrum = spectrum;

    Light *light;
    light = (Light *)malloc(sizeof(Light));
    light->lightData = (void *)data;
    light->type = DeltaPosition;
    light->GetLightSample = &PointLightGetLightSample;
    light->GetSpectrum = &PointLightGetSpectrum;
    light->GetSpectrumByDir = &PointLightGetSpectrumByDir;
    light->LightFree = &PointLightFree;
    return light;
}

void PointLightFree(Light *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->lightData != NULL) {
        free(this->lightData);
    }
    if (freeThis) {
        free(this);
    }
}

Spectrum PointLightGetLightSample(Light *this, Point3 *p ,double *pdf, Sampler *sampler) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return SpectrumInit(0, 0, 0);
    }
#endif
    *p = ((PointLightData *)(this->lightData))->pos;
    *pdf = 1.0;
    return ((PointLightData *)(this->lightData))->spectrum;
}

// Note: This function won't be called if the program runs correctly.
Spectrum PointLightGetSpectrum(Light *this) {
    assert(false);
    return SpectrumInit(0, 0, 0);
}

// Note: This function won't be called if the program runs correctly.
Spectrum PointLightGetSpectrumByDir(Light *this, Vector3 dir) {
    assert(false);
    return SpectrumInit(0, 0, 0);
}
