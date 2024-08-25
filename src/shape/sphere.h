// sphere.h

#ifndef _SPHERE_H_ // _SPHERE_H_
#define _SPHERE_H_

#include <stdbool.h>

#include "../base/shape.h"
#include "../base/point3.h"
#include "../base/sampler.h"
#include "../base/ray.h"
#include "../base/intersectinfo.h"
#include "../base/transform.h"

typedef struct SphereData {
    double radius;
} SphereData;


// Sphere Constructor
Shape SphereInit(double radius, Transform obj2world);

// Sphere New Constructor
Shape * SphereNew(double radius, Transform obj2world);

// Sphere Deconstructor
void SphereFree(Shape *this, bool freeThis);


bool SphereIntersect(Shape *this, Ray ray, IntersectInfo *isect);

bool SphereIsIntersect(Shape *this, Ray ray);

void SphereGetSamplePoint(Shape *this, Point3 *p, double *pdf, Sampler *sampler);

#endif // _SPHERE_H_
