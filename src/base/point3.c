// point3.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "point3.h"
#include "utils.h"

inline Point3 Point3Init(double x, double y, double z) {
    Point3 p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

inline Point3 * Point3New(double x, double y, double z) {
    Point3 *p;
    p = (Point3 *)malloc(sizeof(Point3));
    p->x = x;
    p->y = y;
    p->z = z;
    return p;
}

inline void Point3Free(Point3 *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline Point3 Point3Add(Point3 a, Point3 b) {
    return Point3Init(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Point3 Point3Minus(Point3 a, Point3 b) {
    return Point3Init(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Point3 Point3Neg(Point3 p) {
    return Point3Init(-p.x, -p.y, -p.z);
}

inline Point3 Point3Abs(Point3 p) {
    return Point3Init(fabs(p.x), fabs(p.y), fabs(p.z));
}

inline double Point3LengthSquared(Point3 p) {
    return (p.x * p.x + p.y * p.y + p.z * p.z);
}

inline double Point3Length(Point3 p) {
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

inline double Point3DistanceSquared(Point3 a, Point3 b) {
    return Point3LengthSquared(Point3Minus(b, a));
}

inline double Point3Distance(Point3 a, Point3 b) {
    return Point3Length(Point3Minus(b, a));
}

inline Point3 Point3Lerp(double t, Point3 a, Point3 b) {
    return Point3Init((1.0 - t) * a.x + t * b.x, (1.0 - t) * a.y + t * b.y, (1.0 - t) * a.z + t * b.z);
}

inline Point3 Point3Min(Point3 a, Point3 b) {
    return Point3Init(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z));
}

inline Point3 Point3Max(Point3 a, Point3 b) {
    return Point3Init(MAX(a.x, b.x), MAX(a.y, b.y), MIN(a.z, b.z));
}

inline double Point3MinItem(Point3 p) {
    return MIN(MIN(p.x, p.y), p.z);
}

inline double Point3MaxItem(Point3 p) {
    return MAX(MAX(p.x, p.y), p.z);
}

inline uint32 Point3MinIndex(Point3 p) {
    return MININDEX3(p.x, p.y, p.z);
}

inline uint32 Point3MaxIndex(Point3 p) {
    return MAXINDEX3(p.x, p.y, p.z);
}

inline double Point3NthItem(Point3 p, uint32 n) {
#ifndef NODEBUG
    assert(n <= 2);
#endif

    return *(double *)((char *)&p + n * sizeof(double));

    // Note: Here we don't check if n is in range 0-2 in order to improve the performance.
    //
    // The implementation below is an alternative one.
    //
    // if (n == 0) {
    //     return p.x;
    // }
    // else if (n == 1) {
    //     return p.y;
    // }
    // else if (n == 2) {
    //     return p.z;
    // }
    // else {
    //     return 0;
    // }
}

inline Point3 Point3Permute(Point3 p, uint32 x_index, uint32 y_index, uint32 z_index) {
    return Point3Init(Point3NthItem(p, x_index), Point3NthItem(p, y_index), Point3NthItem(p, z_index));
}

inline void Point3DoAdd(Point3 *this, Point3 p) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
    }
#endif
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;
}

inline void Point3DoMinus(Point3 *this, Point3 p) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
    }
#endif
    this->x -= p.x;
    this->y -= p.y;
    this->z -= p.z;
}

inline void Point3DoNeg(Point3 *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
    }
#endif
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

inline void Point3DoAbs(Point3 *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
    }
#endif
    this->x = fabs(this->x);
    this->y = fabs(this->y);
    this->z = fabs(this->z);
}

inline void Point3DoMin(Point3 *this, Point3 p) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
    }
#endif
    *this = Point3Min(*this, p);
}

inline void Point3DoMax(Point3 *this, Point3 p) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
    }
#endif
    *this = Point3Max(*this, p);
}

inline void Point3DoPermute(Point3 *this, uint32 x_index, uint32 y_index, uint32 z_index) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
    }
#endif
    *this = Point3Permute(*this, x_index, y_index, z_index);
}
