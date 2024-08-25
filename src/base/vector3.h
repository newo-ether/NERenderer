// vector3.h

#ifndef _VECTOR3_H_ // _VECTOR3_H_
#define _VECTOR3_H_

#include <stdbool.h>
#include "array3.h"

#ifndef _UINT32_ // _UINT32_
#define _UINT32_

typedef unsigned int uint32;

#endif // _UINT32_

typedef struct Array3 Vector3;


// Vector3 Constructor
inline Vector3 Vector3Init(double x, double y, double z);

// Vector3 New Constructor
inline Vector3 * Vector3New(double x, double y, double z);

// Vector3 Deconstructor
inline void Vector3Free(Vector3 *this, bool freeThis);


inline Vector3 Vector3Add(Vector3 a, Vector3 b);

inline Vector3 Vector3Minus(Vector3 a, Vector3 b);

inline Vector3 Vector3Mul(Vector3 v, double n);

inline Vector3 Vector3Div(Vector3 v, double n);

inline Vector3 Vector3Neg(Vector3 v);

inline Vector3 Vector3Abs(Vector3 v);

inline double Vector3Dot(Vector3 a, Vector3 b);

inline double Vector3AbsDot(Vector3 a, Vector3 b);

inline Vector3 Vector3Cross(Vector3 a, Vector3 b);

inline double Vector3LengthSquared(Vector3 v);

inline double Vector3Length(Vector3 v);

inline Vector3 Vector3Normalize(Vector3 v);

inline Vector3 Vector3Min(Vector3 a, Vector3 b);

inline Vector3 Vector3Max(Vector3 a, Vector3 b);

inline double Vector3MinItem(Vector3 v);

inline double Vector3MaxItem(Vector3 v);

inline uint32 Vector3MinIndex(Vector3 v);

inline uint32 Vector3MaxIndex(Vector3 v);

inline double Vector3NthItem(Vector3 v, uint32 n);

inline Vector3 Vector3Permute(Vector3 v, uint32 x_index, uint32 y_index, uint32 z_index);

inline void Vector3CoordinateSystem(Vector3 a, Vector3 *b, Vector3 *c);


inline void Vector3DoAdd(Vector3 *this, Vector3 v);

inline void Vector3DoMinus(Vector3 *this, Vector3 v);

inline void Vector3DoMul(Vector3 *this, double n);

inline void Vector3DoDiv(Vector3 *this, double n);

inline void Vector3DoNeg(Vector3 *this);

inline void Vector3DoAbs(Vector3 *this);

inline void Vector3DoCross(Vector3 *this, Vector3 v);

inline void Vector3DoNormalize(Vector3 *this);

inline void Vector3DoMin(Vector3 *this, Vector3 v);

inline void Vector3DoMax(Vector3 *this, Vector3 v);

inline void Vector3DoPermute(Vector3 *this, uint32 x_index, uint32 y_index, uint32 z_index);

#endif // _VECTOR3_H_
