// point3.h

#ifndef _POINT3_H_ // _POINT3_H_
#define _POINT3_H_

#include <stdbool.h>
#include "array3.h"

#ifndef _UINT32_ // _UINT32_
#define _UINT32_

typedef unsigned int uint32;

#endif //_UINT32_

typedef struct Array3 Point3;


// Point3 Constructor
inline Point3 Point3Init(double x, double y, double z);

// Point3 New Constructor
inline Point3 * Point3New(double x, double y, double z);

// Point3 Deconstructor
inline void Point3Free(Point3 *this, bool freeThis);


inline Point3 Point3Add(Point3 a, Point3 b);

inline Point3 Point3Minus(Point3 a, Point3 b);

inline Point3 Point3Neg(Point3 p);

inline Point3 Point3Abs(Point3 p);

inline double Point3LengthSquared(Point3 p);

inline double Point3Length(Point3 p);

inline double Point3DistanceSquared(Point3 a, Point3 b);

inline double Point3Distance(Point3 a, Point3 b);

inline Point3 Point3Lerp(double t, Point3 a, Point3 b);

inline Point3 Point3Min(Point3 a, Point3 b);

inline Point3 Point3Max(Point3 a, Point3 b);

inline double Point3MinItem(Point3 p);

inline double Point3MaxItem(Point3 p);

inline uint32 Point3MinIndex(Point3 p);

inline uint32 Point3MaxIndex(Point3 p);

inline double Point3NthItem(Point3 p, uint32 n);

inline Point3 Point3Permute(Point3 p, uint32 x_index, uint32 y_index, uint32 z_index);


inline void Point3DoAdd(Point3 *this, Point3 p);

inline void Point3DoMinus(Point3 *this, Point3 p);

inline void Point3DoNeg(Point3 *this);

inline void Point3DoAbs(Point3 *this);

inline void Point3DoMin(Point3 *this, Point3 p);

inline void Point3DoMax(Point3 *this, Point3 p);

inline void Point3DoPermute(Point3 *this, uint32 x_index, uint32 y_index, uint32 z_index);

#endif // _POINT3_H_
