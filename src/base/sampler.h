// sampler.h

#ifndef _SAMPLER_H_ // _SAMPLER_H_
#define _SAMPLER_H_

#include <stdbool.h>

#include "vector3.h"

typedef struct Sampler {
    int seed;
} Sampler;

// Sampler Constructor
inline Sampler SamplerInit(int seed);

// Sampler New Constructor
inline Sampler * SamplerNew(int seed);

// Sampler Deconstructor
inline void SamplerFree(Sampler *this, bool freeThis);


inline double SamplerGenerateRandom(Sampler *this);

inline Vector3 SamplerGenerateRandomSphereDir(Sampler *this, double *pdf);

inline Vector3 SamplerGenerateRandomHemisphereDir(Sampler *this, Vector3 normal, double *pdf);

#endif // _SAMPLER_H_
