// transform.h

#ifndef _TRANSFORM_H_ // _TRANSFORM_H_
#define _TRANSFORM_H_

#include <stdbool.h>

#include "matrix.h"
#include "point3.h"
#include "vector3.h"
#include "ray.h"

typedef struct Transform {
    struct Mat4x4 mat;
    struct Mat4x4 matInv;
} Transform;


// Transform Constructor
inline Transform TransformInit(double a00, double a01, double a02, double a03,
                               double a10, double a11, double a12, double a13,
                               double a20, double a21, double a22, double a23,
                               double a30, double a31, double a32, double a33);

// Transform New Constructor
inline Transform * TransformNew(double a00, double a01, double a02, double a03,
                                double a10, double a11, double a12, double a13,
                                double a20, double a21, double a22, double a23,
                                double a30, double a31, double a32, double a33);

// Transform Constructor full version
inline Transform TransformInitAll(double a00, double a01, double a02, double a03,
                                  double a10, double a11, double a12, double a13,
                                  double a20, double a21, double a22, double a23,
                                  double a30, double a31, double a32, double a33,

                                  double aInv00, double aInv01, double aInv02, double aInv03,
                                  double aInv10, double aInv11, double aInv12, double aInv13,
                                  double aInv20, double aInv21, double aInv22, double aInv23,
                                  double aInv30, double aInv31, double aInv32, double aInv33);

// Transform New Constructor full version
inline Transform * TransformNewAll(double a00, double a01, double a02, double a03,
                                   double a10, double a11, double a12, double a13,
                                   double a20, double a21, double a22, double a23,
                                   double a30, double a31, double a32, double a33,

                                   double aInv00, double aInv01, double aInv02, double aInv03,
                                   double aInv10, double aInv11, double aInv12, double aInv13,
                                   double aInv20, double aInv21, double aInv22, double aInv23,
                                   double aInv30, double aInv31, double aInv32, double aInv33);

// Transform Constructor using mat
inline Transform TransformInitFromMat(Mat4x4 mat);

// Transform New Constructor using mat
inline Transform * TransformNewFromMat(Mat4x4 mat);

// Transform Constructor using mat and matInv
inline Transform TransformInitFromMatAndMatInv(Mat4x4 mat, Mat4x4 matInv);

// Transform New Constructor using mat and matInv
inline Transform * TransformNewFromMatAndMatInv(Mat4x4 mat, Mat4x4 matInv);

// Transform Deconstructor
inline void TransformFree(Transform *this, bool freeThis);


inline Transform TransformGenerateIdentity();

inline Transform TransformGenerateTranslate(Vector3 delta);

inline Transform TransformGenerateScale(double x_scale, double y_scale, double z_scale);

inline Transform TransformGenerateRotateX(double degree);

inline Transform TransformGenerateRotateY(double degree);

inline Transform TransformGenerateRotateZ(double degree);

inline Transform TransformGenerateRotate(Vector3 axis, double degree);

inline Transform TransformGenerateLookAt(Point3 pos, Point3 look, Vector3 up);

inline Transform TransformGeneratePerspective(double fov, double near, double far);


inline Transform TransformMul(Transform a, Transform b);

inline Transform TransformInverse(Transform t);

inline Transform TransformTranspose(Transform t);

inline Transform TransformTranslate(Transform t, Vector3 delta);

inline Transform TransformScale(Transform t, double x_scale, double y_scale, double z_scale);

inline Transform TransformRotateX(Transform t, double degree);

inline Transform TransformRotateY(Transform t, double degree);

inline Transform TransformRotateZ(Transform t, double degree);

inline Transform TransformRotate(Transform t, Vector3 axis, double degree);


inline void TransformDoLeftMul(Transform *this, Transform t);

inline void TransformDoRightMul(Transform *this, Transform t);

inline void TransformDoInverse(Transform *this);

inline void TransformDoTranspose(Transform *this);

inline void TransformDoTranslate(Transform *this, Vector3 delta);

inline void TransformDoScale(Transform *this, double x_scale, double y_scale, double z_scale);

inline void TransformDoRotateX(Transform *this, double degree);

inline void TransformDoRotateY(Transform *this, double degree);

inline void TransformDoRotateZ(Transform *this, double degree);

inline void TransformDoRotate(Transform *this, Vector3 axis, double degree);


inline Point3 TransformPoint3(Transform t, Point3 p);

inline Vector3 TransformVector3(Transform t, Vector3 v, bool isNormal);

inline Ray TransformRay(Transform t, Ray ray);


inline void TransformDoPoint3(Transform t, Point3 *p);

inline void TransformDoVector3(Transform t, Vector3 *v, bool isNormal);

inline void TransformDoRay(Transform t, Ray *ray);

#endif // _TRANSFORM_H_
