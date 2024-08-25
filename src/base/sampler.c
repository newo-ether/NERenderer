// sampler.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "sampler.h"
#include "transform.h"
#include "point3.h"
#include "vector3.h"
#include "utils.h"

inline Sampler SamplerInit(int seed) {
    Sampler sampler;
    sampler.seed = seed;
    return sampler;
}

inline Sampler * SamplerNew(int seed) {
    Sampler *sampler;
    sampler = (Sampler *)malloc(sizeof(Sampler));
    sampler->seed = seed;
    return sampler;
}

inline void SamplerFree(Sampler *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline double SamplerGenerateRandom(Sampler *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    int rand_num;
    srand(this->seed);
    rand_num = rand();
    this->seed = rand_num;
    return (double)rand_num / RAND_MAX;
}

inline Vector3 SamplerGenerateRandomSphereDir(Sampler *this, double *pdf) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return Vector3Init(0, 0, 0);
    }
#endif
    double z, r, phi;
    z = SamplerGenerateRandom(this) * 2 - 1.0;
    r = sqrt(MAX(0, 1 - z * z));
    phi = 2 * PI * SamplerGenerateRandom(this);
    *pdf = 1 / (4 * PI);
    return Vector3Init(r * cos(phi), r * sin(phi), z);
}

inline Vector3 SamplerGenerateRandomHemisphereDir(Sampler *this, Vector3 normal, double *pdf) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return Vector3Init(0, 0, 0);
    }
#endif
    Transform t;
    Vector3 v;
    Vector3 norm, x, y;
    double z, r, phi;
    z = SamplerGenerateRandom(this);
    r = sqrt(MAX(0, 1 - z * z));
    phi = 2 * PI * SamplerGenerateRandom(this);
    *pdf = 1 / (2 * PI);
    v = Vector3Init(r * cos(phi), r * sin(phi), z);
    norm = Vector3Normalize(normal);
    Vector3CoordinateSystem(norm, &x, &y);

    // Set the inverse of the matrix to identity matrix in order to avoid unnecessary computations.
    t = TransformInitAll(x.z, y.z, norm.z, 0,
                         x.y, y.y, norm.y, 0,
                         x.x, y.x, norm.x, 0,
                         0,   0,   0,      1,

                         1,   0,   0,      0,
                         0,   1,   0,      0,
                         0,   0,   1,      0,
                         0,   0,   0,      1);

    return TransformVector3(t, v, false);
}
