// ray.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>

#include "ray.h"
#include "point3.h"

inline Ray RayInit(Point3 origin, Vector3 dir, double tMin, double tMax) {
    Ray ray;
    ray.origin = origin;
    ray.dir = dir;
    ray.tMin = tMin;
    ray.tMax = tMax;
    return ray;
}

inline Ray * RayNew(Point3 origin, Vector3 dir, double tMin, double tMax) {
    Ray *ray;
    ray = (Ray *)malloc(sizeof(Ray));
    ray->origin = origin;
    ray->dir = dir;
    ray->tMin = tMin;
    ray->tMax = tMax;
    return ray;
}

inline void RayFree(Ray *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline Point3 RayGetPoint(Ray *this, double t) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return Point3Init(0, 0, 0);
    }
#endif
    return Point3Add(this->origin, (Point3)Vector3Mul(this->dir, t));
}
