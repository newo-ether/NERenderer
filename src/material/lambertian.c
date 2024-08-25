// lambertian.c

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>

#include "lambertian.h"
#include "../base/material.h"
#include "../base/spectrum.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/utils.h"

inline Material LambertianInit(Spectrum kd) {
    LambertianData *data;
    data = (LambertianData *)malloc(sizeof(LambertianData));
    data->kd = kd;

    Material material;
    material.materialData = data;
    material.BSDF = &LambertianBSDF;
    material.MaterialFree = &LambertianFree;

    return material;
}

inline Material * LambertianNew(Spectrum kd) {
    LambertianData *data;
    data = (LambertianData *)malloc(sizeof(LambertianData));
    data->kd = kd;

    Material *material;
    material = (Material *)malloc(sizeof(Material));
    material->materialData = data;
    material->BSDF = &LambertianBSDF;
    material->MaterialFree = &LambertianFree;

    return material;
}

inline void LambertianFree(Material *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline Spectrum LambertianBSDF(Material *this, Vector3 wi, Vector3 wo, Vector3 normal) {
    return SpectrumDiv(((LambertianData *)(this->materialData))->kd, PI);
}
