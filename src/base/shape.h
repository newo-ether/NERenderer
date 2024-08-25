// shape.h

#ifndef _SHAPE_H_ // _SHAPE_H_
#define _SHAPE_H_

#include <stdbool.h>

#include "transform.h"
#include "intersectinfo.h"
#include "point3.h"
#include "sampler.h"
#include "ray.h"

/* *** Shape Interface Struct ***
 *
 * [Member]:
 * - void *shapeData: A pointer to the descriptive data or parameter(s) that are used to represent this Shape.
 * - Transform obj2world: A transformation matrix from the object space to the world wpace.
 * - Transform world2obj: A transformation matrix from the world space to the object space.
 * 
 * [Method]:
 * - bool Intersect(Shape *this, Ray ray, Intersectinfo *isect): Returns a boolean value that describes whether the ray hits this Shape or not, and fills the isect with the corresponding Intersectinfo.
 * - bool IsIntersect(Shape *this, Ray ray): Almost the same as Intersect, but it doesn't return the specific Intersectinfo.
 * - void GetSamplePoint(Shape *this, Point3 *p, double *pdf, Sampler *sampler): Generate a sample point on the surface of this Shape.
 * - void ShapeFree(Shape *this, bool freeThis): This method provides support to different deallocation strategies.
 */

typedef struct IntersectInfo IntersectInfo;

typedef struct Shape {
    void *shapeData;
    struct Transform obj2world;
    struct Transform world2obj;
    bool (* Intersect)(struct Shape *this, struct Ray ray, struct IntersectInfo *isect);
    bool (* IsIntersect)(struct Shape *this, struct Ray ray);
    void (* GetSamplePoint)(struct Shape *this, Point3 *p, double *pdf, struct Sampler *sampler);
    void (* ShapeFree)(struct Shape *this, bool freeThis);
} Shape;

// Note: The constructor and the deconstructor are implemented in the actual shape struct.

#endif // _SHAPE_H_
