// vector3.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "vector3.h"
#include "utils.h"

inline Vector3 Vector3Init(double x, double y, double z) {
    Vector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

inline Vector3 * Vector3New(double x, double y, double z) {
    Vector3 *v;
    v = (Vector3 *)malloc(sizeof(Vector3));
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

inline void Vector3Free(Vector3 *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline Vector3 Vector3Add(Vector3 a, Vector3 b) {
    return Vector3Init(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3 Vector3Minus(Vector3 a, Vector3 b) {
    return Vector3Init(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vector3 Vector3Mul(Vector3 v, double n) {
    return Vector3Init(v.x * n, v.y * n, v.z * n);
}

inline Vector3 Vector3Div(Vector3 v, double n) {
    double nInv;
    nInv = 1.0 / n;
    return Vector3Init(v.x * nInv, v.y * nInv, v.z * nInv);
}

inline Vector3 Vector3Neg(Vector3 v) {
    return Vector3Init(-v.x, -v.y, -v.z);
}

inline Vector3 Vector3Abs(Vector3 v) {
    return Vector3Init(fabs(v.x), fabs(v.y), fabs(v.z));
}

inline double Vector3Dot(Vector3 a, Vector3 b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline double Vector3AbsDot(Vector3 a, Vector3 b) {
    return fabs(a.x * b.x + a.y * b.y + a.z * b.z);
}

inline Vector3 Vector3Cross(Vector3 a, Vector3 b) {
    return Vector3Init(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline double Vector3LengthSquared(Vector3 v) {
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

inline double Vector3Length(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vector3 Vector3Normalize(Vector3 v) {
    return Vector3Div(v, Vector3Length(v));
}

inline Vector3 Vector3Min(Vector3 a, Vector3 b) {
    return Vector3Init(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z));
}

inline Vector3 Vector3Max(Vector3 a, Vector3 b) {
    return Vector3Init(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z));
}

inline double Vector3MinItem(Vector3 v) {
    return MIN(MIN(v.x, v.y), v.z);
}

inline double Vector3MaxItem(Vector3 v) {
    return MAX(MAX(v.x, v.y), v.z);
}

inline uint32 Vector3MinIndex(Vector3 v) {
    return MININDEX3(v.x, v.y, v.z);
}

inline uint32 Vector3MaxIndex(Vector3 v) {
    return MAXINDEX3(v.x, v.y, v.z);
}

inline double Vector3NthItem(Vector3 v, uint32 n) {
#ifndef NODEBUG
    assert(n <= 2);
#endif

    return *(double *)((char *)&v + n * sizeof(double));

    // Note: Here we don't check if n is in range 0-2 in order to improve the performance.
    //
    // The implementation below is an alternative one.
    //
    // if (n == 0) {
    //     return v.x;
    // }
    // else if (n == 1) {
    //     return v.y;
    // }
    // else if (n == 2) {
    //     return v.z;
    // }
    // else {
    //     return 0;
    // }
}

inline Vector3 Vector3Permute(Vector3 v, uint32 x_index, uint32 y_index, uint32 z_index) {
    return Vector3Init(Vector3NthItem(v, x_index), Vector3NthItem(v, y_index), Vector3NthItem(v, z_index));
}

inline void Vector3CoordinateSystem(Vector3 a, Vector3 *b, Vector3 *c) {
    if (a.x > a.y) {
        *b = Vector3Div(Vector3Init(-a.z, 0, a.x), sqrt(a.x * a.x + a.z * a.z));
    }
    else {
        *b = Vector3Div(Vector3Init(0, a.z, -a.y), sqrt(a.y * a.y + a.z * a.z));
    }
    *c = Vector3Cross(a, *b);
}

// Note: Here we don't check if "this" is a nullptr in order to improve the performance.

inline void Vector3DoAdd(Vector3 *this, Vector3 v) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}

inline void Vector3DoMinus(Vector3 *this, Vector3 v) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
}

inline void Vector3DoMul(Vector3 *this, double n) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->x *= n;
    this->y *= n;
    this->z *= n;
}

inline void Vector3DoDiv(Vector3 *this, double n) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    double nInv;
    nInv = 1.0 / n;
    this->x *= nInv;
    this->y *= nInv;
    this->z *= nInv;
}

inline void Vector3DoNeg(Vector3 *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

inline void Vector3DoAbs(Vector3 *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->x = fabs(this->x);
    this->y = fabs(this->y);
    this->z = fabs(this->z);
}

inline void Vector3DoCross(Vector3 *this, Vector3 v) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    *this = Vector3Cross(*this, v);
}

inline void Vector3DoNormalize(Vector3 *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    *this = Vector3Normalize(*this);
}

inline void Vector3DoMin(Vector3 *this, Vector3 v) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    *this = Vector3Min(*this, v);
}

inline void Vector3DoMax(Vector3 *this, Vector3 v) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    *this = Vector3Max(*this, v);
}

inline void Vector3DoPermute(Vector3 *this, uint32 x_index, uint32 y_index, uint32 z_index) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    *this = Vector3Permute(*this, x_index, y_index, z_index);
}
