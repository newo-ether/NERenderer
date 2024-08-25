// arealight.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>

#include "arealight.h"
#include "../base/light.h"
#include "../base/spectrum.h"
#include "../base/sampler.h"
#include "../base/shape.h"
#include "../base/utils.h"

Light AreaLightInit(Shape *shape, Spectrum spectrum) {
    AreaLightData *data;
    data = (AreaLightData *)malloc(sizeof(AreaLightData));
    data->shape = shape;
    data->spectrum = spectrum;

    Light light;
    light.lightData = (void *)data;
    light.type = Area;
    light.GetLightSample = &AreaLightGetLightSample;
    light.GetSpectrum = &AreaLightGetSpectrum;
    light.GetSpectrumByDir = &AreaLightGetSpectrumByDir;
    light.LightFree = &AreaLightFree;
    return light;
}

Light * AreaLightNew(Shape *shape, Spectrum spectrum) {
    AreaLightData *data;
    data = (AreaLightData *)malloc(sizeof(AreaLightData));
    data->shape = shape;
    data->spectrum = spectrum;

    Light *light;
    light = (Light *)malloc(sizeof(Light));
    light->lightData = (void *)data;
    light->type = Area;
    light->GetLightSample = &AreaLightGetLightSample;
    light->GetSpectrum = &AreaLightGetSpectrum;
    light->GetSpectrumByDir = &AreaLightGetSpectrumByDir;
    light->LightFree = &AreaLightFree;
    return light;
}

void AreaLightFree(Light *this, bool freeThis) {
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

Spectrum AreaLightGetLightSample(Light *this, Point3 *p, double *pdf, Sampler *sampler) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return SpectrumInit(0, 0, 0);
    }
#endif
    AreaLightData *data;
    data = (AreaLightData *)(this->lightData);
    data->shape->GetSamplePoint(data->shape, p, pdf, sampler);
    return data->spectrum;
}

Spectrum AreaLightGetSpectrum(Light *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return SpectrumInit(0, 0, 0);
    }
#endif
    return ((AreaLightData *)(this->lightData))->spectrum;
}

// Note: This function won't be called if the program runs correctly.
Spectrum AreaLightGetSpectrumByDir(Light *this, Vector3 dir) {
    assert(false);
    return SpectrumInit(0, 0, 0);
}
