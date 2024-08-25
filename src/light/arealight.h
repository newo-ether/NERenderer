// arealight.h

#ifndef _AREALIGHT_H_ // _AREALIGHT_H_
#define _AREALIGHT_H_

#include <stdbool.h>

#include "../base/light.h"
#include "../base/spectrum.h"
#include "../base/sampler.h"
#include "../base/shape.h"
#include "../base/vector3.h"

typedef struct AreaLightData {
    Shape *shape;
    Spectrum spectrum;
} AreaLightData;


// AreaLight Constructor
Light AreaLightInit(Shape *shape, Spectrum spectrum);

// AreaLight New Constructor
Light * AreaLightNew(Shape *shape, Spectrum spectrum);

// AreaLight Deconstructor
void AreaLightFree(Light *this, bool freeThis);


Spectrum AreaLightGetLightSample(Light *this, Point3 *p, double *pdf, Sampler *sampler);

Spectrum AreaLightGetSpectrum(Light *this);

Spectrum AreaLightGetSpectrumByDir(Light *this, Vector3 dir);

#endif // _AREALIGHT_H_
