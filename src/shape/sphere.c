// sphere.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <assert.h>
#include <malloc.h>

#include "sphere.h"
#include "../base/shape.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/sampler.h"
#include "../base/ray.h"
#include "../base/intersectinfo.h"
#include "../base/transform.h"
#include "../base/utils.h"

Shape SphereInit(double radius, Transform obj2world) {
    SphereData *data = (SphereData *)malloc(sizeof(SphereData));
    data->radius = radius;

    Shape shape;
    shape.shapeData = (void *)data;
    shape.obj2world = obj2world;
    shape.world2obj = TransformInverse(obj2world);
    shape.Intersect = &SphereIntersect;
    shape.IsIntersect = &SphereIsIntersect;
    shape.GetSamplePoint = &SphereGetSamplePoint;
    shape.ShapeFree = &SphereFree;
    
    return shape;
}

Shape * SphereNew(double radius, Transform obj2world) {
    SphereData *data = (SphereData *)malloc(sizeof(SphereData));
    data->radius = radius;
    
    Shape *shape = (Shape *)malloc(sizeof(Shape));
    shape->shapeData = (void *)data;
    shape->obj2world = obj2world;
    shape->world2obj = TransformInverse(obj2world);
    shape->Intersect = &SphereIntersect;
    shape->IsIntersect = &SphereIsIntersect;
    shape->GetSamplePoint = &SphereGetSamplePoint;
    shape->ShapeFree = &SphereFree;
    
    return shape;
}

void SphereFree(Shape *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->shapeData != NULL) {
        free(this->shapeData);
    }
    if (freeThis) {
        free(this);
    }
}

bool SphereIntersect(Shape *this, Ray ray, IntersectInfo *isect) {
    double radius, a, b, c, t0, t1;
    Ray r;
    Vector3 o, d, n;
    Point3 p;

#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return false;
    }
#endif

    // Transform the ray from the world space to the object space.
    r = TransformRay(this->world2obj, ray);

    // Get data from the shapeData and compute basic values for solving the intersection point.
    radius = ((SphereData *)(this->shapeData))->radius;
    o = r.origin;
    d = r.dir;
    a = d.x * d.x + d.y * d.y + d.z * d.z;
    b = 2 * (d.x * o.x + d.y * o.y + d.z * o.z);
    c = o.x * o.x + o.y * o.y + o.z * o.z - radius * radius;

    // Solve for any intersection point available.
    if (SolveQuadraticEquation(a, b, c, &t0, &t1)) {
        // Note: t0 is guaranteed to be smaller than t1.
        if (t0 > ray.tMin && t0 < ray.tMax) {
            p = RayGetPoint(&ray, t0);
            n = (Vector3)p;

            // Remap the intersection to the surface of the sphere and move the intersection point up along the normal by Epsilon.
            p = Vector3Add(Vector3Mul((Vector3)p, radius / Point3Length(p)), Vector3Mul(Vector3Normalize(n), Epsilon));

            // Set up the intersection info.
            *isect = IntersectInfoInit(
                    t0, 
                    TransformPoint3(this->obj2world, p),
                    Vector3Normalize(TransformVector3(this->obj2world, n, true)),
                    Point3Neg(ray.dir),
                    NULL);

            return true;
        }
        else if (t1 > ray.tMin && t1 < ray.tMax) {
            p = RayGetPoint(&ray, t1);
            n = (Vector3)p;

            // Remap the intersection to the surface of the sphere and move the intersection point up along the normal by Epsilon.
            p = Vector3Add(Vector3Mul((Vector3)p, radius / Point3Length(p)), Vector3Mul(Vector3Normalize(n), Epsilon));

            // Set up the intersection info.
            *isect = IntersectInfoInit(
                    t1, 
                    TransformPoint3(this->obj2world, p),
                    Vector3Normalize(TransformVector3(this->obj2world, n, true)),
                    Point3Neg(ray.dir),
                    NULL);

            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool SphereIsIntersect(Shape *this, Ray ray) {
    double radius, a, b, c, t0, t1;
    Ray r;
    Vector3 o, d;

#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return false;
    }
#endif

    // Transform the ray from the world space to the object space.
    r = TransformRay(this->world2obj, ray);

    // Get data from the shapeData and compute basic values for solving the intersection point.
    radius = ((SphereData *)(this->shapeData))->radius;
    o = r.origin;
    d = r.dir;
    a = d.x * d.x + d.y * d.y + d.z * d.z;
    b = 2 * (d.x * o.x + d.y * o.y + d.z * o.z);
    c = o.x * o.x + o.y * o.y + o.z * o.z - radius * radius;

    // Solve for any intersection point available.
    if (SolveQuadraticEquation(a, b, c, &t0, &t1)) {
        if ((t0 > ray.tMin && t0 < ray.tMax) || (t1 > ray.tMin && t1 < ray.tMax)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void SphereGetSamplePoint(Shape *this, Point3 *p, double *pdf, Sampler *sampler) {
    double radius;
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    radius = ((SphereData *)(this->shapeData))->radius;
    *p = Vector3Mul(SamplerGenerateRandomSphereDir(sampler, pdf), radius);
}
