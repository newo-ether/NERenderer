// intersectinfo.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>

#include "intersectinfo.h"
#include "object.h"
#include "point3.h"
#include "vector3.h"

IntersectInfo IntersectInfoInit(double tHit, Point3 hitPoint, Vector3 hitNormal, Vector3 incomeDir, Object *hitObj) {
    IntersectInfo isect;
    isect.tHit = tHit;
    isect.hitPoint = hitPoint;
    isect.hitNormal = hitNormal;
    isect.incomeDir = incomeDir;
    isect.hitObj = hitObj;
    return isect;
}

IntersectInfo * IntersectInfoNew(double tHit, Point3 hitPoint, Vector3 hitNormal, Vector3 incomeDir, Object *hitObj) {
    IntersectInfo *isect;
    isect = (IntersectInfo *)malloc(sizeof(IntersectInfo));
    isect->tHit = tHit;
    isect->hitPoint = hitPoint;
    isect->hitNormal = hitNormal;
    isect->incomeDir = incomeDir;
    isect->hitObj = hitObj;
    return isect;
}

void IntersectInfoFree(IntersectInfo *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->hitObj != NULL) {
        ObjectFree(this->hitObj, true);
    }
    if (freeThis) {
        free(this);
    }
}
