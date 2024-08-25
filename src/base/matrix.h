// matrix.h

#ifndef _MATRIX_H_ // _MATRIX_H_
#define _MATRIX_H_

#include <stdbool.h>

#define MAT_SIZE (4 * 4 * sizeof(double))

typedef struct Mat4x4 {
    double m[4][4];
} Mat4x4;


// Mat4x4 Constructor
inline Mat4x4 Mat4x4Init(double a00, double a01, double a02, double a03,
                         double a10, double a11, double a12, double a13,
                         double a20, double a21, double a22, double a23,
                         double a30, double a31, double a32, double a33);

// Mat4x4 New Constructor
inline Mat4x4 * Mat4x4New(double a00, double a01, double a02, double a03,
                          double a10, double a11, double a12, double a13,
                          double a20, double a21, double a22, double a23,
                          double a30, double a31, double a32, double a33);

// Mat4x4 Deconstructor
inline void Mat4x4Free(Mat4x4 *this, bool freeThis);


inline Mat4x4 Mat4x4GenerateIdentity();

inline Mat4x4 Mat4x4Mul(Mat4x4 mat_a, Mat4x4 mat_b);

inline Mat4x4 Mat4x4Transpose(Mat4x4 mat);

inline Mat4x4 Mat4x4Inverse(Mat4x4 mat);

inline void Mat4x4DoLeftMul(Mat4x4 *this, Mat4x4 mat);

inline void Mat4x4DoRightMul(Mat4x4 *this, Mat4x4 mat);

inline void Mat4x4DoTranspose(Mat4x4 *this);

#endif // _MATRIX_H_
