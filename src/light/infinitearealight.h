// infinitearealight.h

#ifndef _INFINITEAREALIGHT_H_ // _INFINITEAREALIGHT_H_
#define _INFINITEAREALIGHT_H_

#include <stdbool.h>

#include "../image/image.h"
#include "../base/light.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/sampler.h"

typedef struct InfiniteAreaLightData {
    Image *spectrumLUT;
} InfiniteAreaLightData;


// InfiniteAreaLight Constructor
Light InfiniteAreaLightInit(Image *spectrumLUT);

// InfiniteAreaLight New Constructor
Light * InfiniteAreaLightNew(Image *spectrumLUT);

// InfiniteAreaLight Deconstructor
void InfiniteAreaLightFree(Light *this, bool freeThis);


Spectrum InfiniteAreaLightGetLightSample(Light *this, Point3 *p, double *pdf, Sampler *sampler);

Spectrum InfiniteAreaLightGetSpectrum(Light *this);

Spectrum InfiniteAreaLightGetSpectrumByDir(Light *this, Vector3 dir);

#endif // _INFINITEAREALIGHT_H_
