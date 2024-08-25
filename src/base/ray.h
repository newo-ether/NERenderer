// ray.h

#ifndef _RAY_H_ // _RAY_H_
#define _RAY_H_

#include <stdbool.h>
#include "point3.h"
#include "vector3.h"

typedef struct Ray {
    Point3 origin;
    Vector3 dir;
    double tMin;
    double tMax;
} Ray;


// Ray Constructor
inline Ray RayInit(Point3 origin, Vector3 dir, double tMin, double tMax);

// Ray New Constructor
inline Ray * RayNew(Point3 origin, Vector3 dir, double tMin, double tMax);

// Ray Deconstructor
inline void RayFree(Ray *this, bool freeThis);


inline Point3 RayGetPoint(Ray *this, double t);

#endif // _RAY_H_
