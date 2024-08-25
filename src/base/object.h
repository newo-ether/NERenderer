// object.h

#ifndef _OBJECT_H_ // _OBJECT_H_
#define _OBJECT_H_

#include <stdbool.h>

#include "shape.h"
#include "light.h"
#include "material.h"
#include "intersectinfo.h"
#include "ray.h"
#include "list.h"

typedef struct IntersectInfo IntersectInfo;

typedef struct Shape Shape;

typedef struct Object {
    struct Shape *shape;
    struct Light *light;
    struct Material *material;
} Object;


// Object Constructor
Object ObjectInit(Shape *shape, Light *light, Material *material);

// Object New Constructor
Object * ObjectNew(Shape *shape, Light *light, Material *material);

// Object Deconstructor
void ObjectFree(Object *this, bool freeThis);


bool ObjectIntersect(List *objects, Ray ray, IntersectInfo *isect);

bool ObjectIsIntersect(List *objects, Ray ray);

#endif // _OBJECT_H_
