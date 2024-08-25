// pointlight.h

#ifndef _POINTLIGHT_H_ // _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include <stdbool.h>

#include "../base/light.h"
#include "../base/spectrum.h"
#include "../base/sampler.h"
#include "../base/point3.h"
#include "../base/vector3.h"

typedef struct PointLightData {
    Point3 pos;
    Spectrum spectrum;
} PointLightData;


// PointLight Constructor
Light PointLightInit(Point3 pos, Spectrum spectrum);

// PointLight New Constructor
Light * PointLightNew(Point3 pos, Spectrum spectrum);

// PointLight Deconstructor
void PointLightFree(Light *this, bool freeThis);


Spectrum PointLightGetLightSample(Light *this, Point3 *p, double *pdf, Sampler *sampler);

Spectrum PointLightGetSpectrum(Light *this);

Spectrum PointLightGetSpectrumByDir(Light *this, Vector3 dir);

#endif // _POINTLIGHT_H_
