// intersectinfo.h

#ifndef _INTERSECTINFO_H_ // _INTERSECTINFO_H_
#define _INTERSECTINFO_H_

#include <stdbool.h>

#include "object.h"
#include "point3.h"
#include "vector3.h"

typedef struct Object Object;

typedef struct IntersectInfo {
    double tHit;
    Point3 hitPoint;
    Vector3 hitNormal;
    Vector3 incomeDir;
    struct Object *hitObj;
} IntersectInfo;


// IntersectInfo Constructor
IntersectInfo IntersectInfoInit(double tHit, Point3 hitPoint, Vector3 hitNormal, Vector3 incomeDir, Object *hitObj);

// IntersectInfo New Constructor
IntersectInfo * IntersectInfoNew(double tHit, Point3 hitPoint, Vector3 hitNormal, Vector3 incomeDir, Object *hitObj);

// IntersectInfo Deconstructor
void IntersectInfoFree(IntersectInfo *this, bool freeThis);


#endif // _INTERSECTINFO_H_
