// object.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>

#include "object.h"
#include "shape.h"
#include "light.h"
#include "material.h"
#include "intersectinfo.h"
#include "ray.h"
#include "list.h"

Object ObjectInit(Shape *shape, Light *light, Material *material) {
    Object object;
    object.shape = shape;
    object.light = light;
    object.material = material;
    return object;
}

Object * ObjectNew(Shape *shape, Light *light, Material *material) {
    Object *object;
    object = (Object *)malloc(sizeof(Object));
    object->shape = shape;
    object->light = light;
    object->material = material;
    return object;
}

void ObjectFree(Object *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->shape != NULL) {
        this->shape->ShapeFree(this->shape, true);
    }
    if (this->light != NULL) {
        this->light->LightFree(this->light, true);
    }
    if (this->material != NULL) {
        this->material->MaterialFree(this->material, true);
    }
    if (freeThis) {
        free(this);
    }
}

bool ObjectIntersect(List *objects, Ray ray, IntersectInfo *isect) {
    bool intersect = false;
    Object *object;
    ListForeachContent(objects, object, Object) {
        if (object->shape->Intersect(object->shape, ray, isect)) {
            intersect = true;
            isect->hitObj = object;
            ray.tMax = isect->tHit;
        }
    }
    return intersect;
}

bool ObjectIsIntersect(List *objects, Ray ray) {
    Object *object;
    ListForeachContent(objects, object, Object) {
        if (object->shape->IsIntersect(object->shape, ray)) {
            return true;
        }
    }
    return false;
}
