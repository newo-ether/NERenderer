// lambertian.h

#ifndef _LAMBERTIAN_H_ // _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include <stdbool.h>

#include "../base/material.h"
#include "../base/spectrum.h"
#include "../base/intersectinfo.h"

typedef struct LambertianData {
    Spectrum kd;
} LambertianData;


// Lambertian Constructor
inline Material LambertianInit(Spectrum kd);

// Lambertian New Constructor
inline Material * LambertianNew(Spectrum kd);

// Lambertian Deconstructor
inline void LambertianFree(Material *this, bool freeThis);


inline Spectrum LambertianBSDF(Material *this, Vector3 wi, Vector3 wo, Vector3 normal);

#endif // _LAMBERTIAN_H_
