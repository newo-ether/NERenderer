// transform.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "transform.h"
#include "matrix.h"
#include "utils.h"
#include "point3.h"
#include "vector3.h"
#include "ray.h"

inline Transform TransformInit(double a00, double a01, double a02, double a03,
                               double a10, double a11, double a12, double a13,
                               double a20, double a21, double a22, double a23,
                               double a30, double a31, double a32, double a33) {
    Transform t;
    t.mat = Mat4x4Init(a00, a01, a02, a03,
                       a10, a11, a12, a13,
                       a20, a21, a22, a23,
                       a30, a31, a32, a33);

    t.matInv = Mat4x4Inverse(t.mat);
    return t;
}

inline Transform * TransformNew(double a00, double a01, double a02, double a03,
                                double a10, double a11, double a12, double a13,
                                double a20, double a21, double a22, double a23,
                                double a30, double a31, double a32, double a33) {
    Transform *t;
    t = (Transform *)malloc(sizeof(Transform));
    t->mat = Mat4x4Init(a00, a01, a02, a03,
                        a10, a11, a12, a13,
                        a20, a21, a22, a23,
                        a30, a31, a32, a33);

    t->matInv = Mat4x4Inverse(t->mat);
    return t;
}

inline Transform TransformInitAll(double a00, double a01, double a02, double a03,
                                  double a10, double a11, double a12, double a13,
                                  double a20, double a21, double a22, double a23,
                                  double a30, double a31, double a32, double a33,

                                  double aInv00, double aInv01, double aInv02, double aInv03,
                                  double aInv10, double aInv11, double aInv12, double aInv13,
                                  double aInv20, double aInv21, double aInv22, double aInv23,
                                  double aInv30, double aInv31, double aInv32, double aInv33) {
    Transform t;
    t.mat = Mat4x4Init(a00, a01, a02, a03,
                       a10, a11, a12, a13,
                       a20, a21, a22, a23,
                       a30, a31, a32, a33);

    t.matInv = Mat4x4Init(aInv00, aInv01, aInv02, aInv03,
                          aInv10, aInv11, aInv12, aInv13,
                          aInv20, aInv21, aInv22, aInv23,
                          aInv30, aInv31, aInv32, aInv33);

    return t;
}

inline Transform * TransformNewAll(double a00, double a01, double a02, double a03,
                                   double a10, double a11, double a12, double a13,
                                   double a20, double a21, double a22, double a23,
                                   double a30, double a31, double a32, double a33,

                                   double aInv00, double aInv01, double aInv02, double aInv03,
                                   double aInv10, double aInv11, double aInv12, double aInv13,
                                   double aInv20, double aInv21, double aInv22, double aInv23,
                                   double aInv30, double aInv31, double aInv32, double aInv33) {
    Transform *t;
    t = (Transform *)malloc(sizeof(Transform));
    t->mat = Mat4x4Init(a00, a01, a02, a03,
                        a10, a11, a12, a13,
                        a20, a21, a22, a23,
                        a30, a31, a32, a33);

    t->matInv = Mat4x4Init(aInv00, aInv01, aInv02, aInv03,
                           aInv10, aInv11, aInv12, aInv13,
                           aInv20, aInv21, aInv22, aInv23,
                           aInv30, aInv31, aInv32, aInv33);

    return t;
}

inline Transform TransformInitFromMat(Mat4x4 mat) {
    Transform t;
    t.mat = mat;
    t.matInv = Mat4x4Inverse(mat);
    return t;
}

inline Transform * TransformNewFromMat(Mat4x4 mat) {
    Transform *t;
    t = (Transform *)malloc(sizeof(Transform));
    t->mat = mat;
    t->matInv = Mat4x4Inverse(mat);
    return t;
}

inline Transform TransformInitFromMatAndMatInv(Mat4x4 mat, Mat4x4 matInv) {
    Transform t;
    t.mat = mat;
    t.matInv = matInv;
    return t;
}

inline Transform * TransformNewFromMatAndMatInv(Mat4x4 mat, Mat4x4 matInv) {
    Transform *t;
    t = (Transform *)malloc(sizeof(Transform));
    t->mat = mat;
    t->matInv = matInv;
    return t;
}

inline void TransformFree(Transform *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline Transform TransformGenerateIdentity() {
    return TransformInitAll(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1,

                            1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1);
}

inline Transform TransformGenerateTranslate(Vector3 delta) {
    return TransformInitAll(1, 0, 0, delta.x,
                            0, 1, 0, delta.y,
                            0, 0, 1, delta.z,
                            0, 0, 0, 1,

                            1, 0, 0, -delta.x,
                            0, 1, 0, -delta.y,
                            0, 0, 1, -delta.z,
                            0, 0, 0, 1);
}

inline Transform TransformGenerateScale(double x_scale, double y_scale, double z_scale) {
    return TransformInitAll(x_scale, 0,       0,       0,
                            0,       y_scale, 0,       0,
                            0,       0,       z_scale, 0,
                            0,       0,       0,       1,

                            1/x_scale, 0,         0,         0,
                            0,         1/y_scale, 0,         0,
                            0,         0,         1/z_scale, 0,
                            0,         0,         0,         1);
}

inline Transform TransformGenerateRotateX(double degree) {
    double theta, cosTheta, sinTheta;
    theta = TORADIAN(degree);
    cosTheta = cos(theta);
    sinTheta = sin(theta);
    return TransformInitAll(1, 0,        0,         0,
                            0, cosTheta, -sinTheta, 0,
                            0, sinTheta, cosTheta,  0,
                            0, 0,        0,         1,

                            1, 0,         0,        0,
                            0, cosTheta,  sinTheta, 0,
                            0, -sinTheta, cosTheta, 0,
                            0, 0,         0,        1);
}

inline Transform TransformGenerateRotateY(double degree) {
    double theta, cosTheta, sinTheta;
    theta = TORADIAN(degree);
    cosTheta = cos(theta);
    sinTheta = sin(theta);
    return TransformInitAll(cosTheta,  0, sinTheta, 0,
                            0,         1, 0,        0,
                            -sinTheta, 0, cosTheta, 0,
                            0,         0, 0,        1,

                            cosTheta, 0, -sinTheta, 0,
                            0,        1, 0,         0,
                            sinTheta, 0, cosTheta,  0,
                            0,        0, 0,         1);
}

inline Transform TransformGenerateRotateZ(double degree) {
    double theta, cosTheta, sinTheta;
    theta = TORADIAN(degree);
    cosTheta = cos(theta);
    sinTheta = sin(theta);
    return TransformInitAll(cosTheta, -sinTheta, 0, 0,
                            sinTheta, cosTheta,  0, 0,
                            0,        0,         1, 0,
                            0,        0,         0, 1,

                            cosTheta,  sinTheta, 0, 0,
                            -sinTheta, cosTheta, 0, 0,
                            0,         0,        1, 0,
                            0,         0,        0, 1);
}

inline Transform TransformGenerateRotate(Vector3 axis, double degree) {
    double theta, cosTheta, sinTheta;
    theta = TORADIAN(degree);
    cosTheta = cos(theta);
    sinTheta = sin(theta);
    Vector3DoNormalize(&axis);
    return TransformInit(axis.x * axis.x + (1 - axis.x * axis.x) * cosTheta,
                         axis.x * axis.y * (1 - cosTheta) - axis.z * sinTheta,
                         axis.x * axis.z * (1 - cosTheta) + axis.y * sinTheta,
                         0,

                         axis.x * axis.y * (1 - cosTheta) + axis.z * sinTheta,
                         axis.y * axis.y + (1 - axis.y * axis.y) * cosTheta,
                         axis.y * axis.z * (1 - cosTheta) - axis.x * sinTheta,
                         0,

                         axis.x * axis.z * (1 - cosTheta) - axis.y * sinTheta,
                         axis.y * axis.z * (1 - cosTheta) + axis.x * sinTheta,
                         axis.z * axis.z + (1 - axis.z * axis.z) * cosTheta,
                         0,

                         0, 0, 0, 1);
}

// Note: NERenderer uses right-handed coordinate system.
inline Transform TransformGenerateLookAt(Point3 pos, Point3 look, Vector3 up) {
    Transform cam2world;
    Vector3 dir, right;
    dir = Vector3Normalize(Point3Minus(look, pos));
    right = Vector3Normalize(Vector3Cross(dir, Vector3Normalize(up)));
    up = Vector3Cross(right, dir);
    cam2world = TransformInit(right.x, up.x, -dir.x, pos.x,
                              right.y, up.y, -dir.y, pos.y,
                              right.z, up.z, -dir.z, pos.z,
                              0,       0,    0,      1);
    return cam2world;
}

// Returns the transformation matrix from the camera space to the NDC space.
// NDC space: x = [-1, 1], y = [-1, 1], z = [0, 1]
// the x = [-1, 1] in the NDC space corresponds to x = [-1/2 * screenWidth, 1/2 * screenWidth] in the camera space.
inline Transform TransformGeneratePerspective(double fov, double near, double far) {
    Transform perspective;
    double scale;
    scale = 1 / (near * tan(TORADIAN(fov / 2)));
    perspective = TransformInit(1, 0, 0,                  0,
                                0, 1, 0,                  0,
                                0, 0, far / (far - near), -far * near / (far - near),
                                0, 0, 1,                  0);
    return TransformMul(perspective, TransformGenerateScale(scale, scale, -1));
}

inline Transform TransformMul(Transform a, Transform b) {
    return TransformInitFromMatAndMatInv(Mat4x4Mul(a.mat, b.mat), Mat4x4Mul(b.matInv, a.matInv));
}

inline Transform TransformInverse(Transform t) {
    return TransformInitFromMatAndMatInv(t.matInv, t.mat);
}

inline Transform TransformTranspose(Transform t) {
    return TransformInitFromMatAndMatInv(Mat4x4Transpose(t.matInv), Mat4x4Transpose(t.mat));
}

inline Transform TransformTranslate(Transform t, Vector3 delta) {
    return TransformMul(TransformGenerateTranslate(delta), t);
}

inline Transform TransformScale(Transform t, double x_scale, double y_scale, double z_scale) {
    return TransformMul(TransformGenerateScale(x_scale, y_scale, z_scale), t);
}

inline Transform TransformRotateX(Transform t, double degree) {
    return TransformMul(TransformGenerateRotateX(degree), t);
}

inline Transform TransformRotateY(Transform t, double degree) {
    return TransformMul(TransformGenerateRotateY(degree), t);
}

inline Transform TransformRotateZ(Transform t, double degree) {
    return TransformMul(TransformGenerateRotateZ(degree), t);
}

inline Transform TransformRotate(Transform t, Vector3 axis, double degree) {
    return TransformMul(TransformGenerateRotate(axis, degree), t);
}

inline void TransformDoLeftMul(Transform *this, Transform t) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    Mat4x4DoLeftMul(&this->mat, t.mat);
    Mat4x4DoRightMul(&this->matInv, t.matInv);
}

inline void TransformDoRightMul(Transform *this, Transform t) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    Mat4x4DoRightMul(&this->mat, t.mat);
    Mat4x4DoLeftMul(&this->matInv, t.matInv);
}

inline void TransformDoInverse(Transform *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    Mat4x4 tmp;
    tmp = this->mat;
    this->mat = this->matInv;
    this->matInv = tmp;
}

inline void TransformDoTranspose(Transform *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    Mat4x4 tmp;
    Mat4x4DoTranspose(&this->mat);
    Mat4x4DoTranspose(&this->matInv);
    tmp = this->mat;
    this->mat = this->matInv;
    this->matInv = tmp;
}

inline void TransformDoTranslate(Transform *this, Vector3 delta) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    TransformDoLeftMul(this, TransformGenerateTranslate(delta));
}

inline void TransformDoScale(Transform *this, double x_scale, double y_scale, double z_scale) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    TransformDoLeftMul(this, TransformGenerateScale(x_scale, y_scale, z_scale));
}

inline void TransformDoRotateX(Transform *this, double degree) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    TransformDoLeftMul(this, TransformGenerateRotateX(degree));
}

inline void TransformDoRotateY(Transform *this, double degree) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    TransformDoLeftMul(this, TransformGenerateRotateY(degree));
}

inline void TransformDoRotateZ(Transform *this, double degree) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    TransformDoLeftMul(this, TransformGenerateRotateZ(degree));
}

inline void TransformDoRotate(Transform *this, Vector3 axis, double degree) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    TransformDoLeftMul(this, TransformGenerateRotate(axis, degree));
}

inline Point3 TransformPoint3(Transform t, Point3 p) {
    double x, y, z, w, wInv;
    
    x = t.mat.m[0][0] * p.x + t.mat.m[0][1] * p.y + t.mat.m[0][2] * p.z + t.mat.m[0][3];
    y = t.mat.m[1][0] * p.x + t.mat.m[1][1] * p.y + t.mat.m[1][2] * p.z + t.mat.m[1][3];
    z = t.mat.m[2][0] * p.x + t.mat.m[2][1] * p.y + t.mat.m[2][2] * p.z + t.mat.m[2][3];
    w = t.mat.m[3][0] * p.x + t.mat.m[3][1] * p.y + t.mat.m[3][2] * p.z + t.mat.m[3][3];

    if (w == 1) {
        return Point3Init(x, y, z);
    }
    else {
        wInv = 1.0 / w;
        return Point3Init(x * wInv, y * wInv, z * wInv);
    }
}

inline Vector3 TransformVector3(Transform t, Vector3 v, bool isNormal) {
    double x, y, z;

    if (isNormal) {
        x = t.matInv.m[0][0] * v.x + t.matInv.m[1][0] * v.y + t.matInv.m[2][0] * v.z;
        y = t.matInv.m[0][1] * v.x + t.matInv.m[1][1] * v.y + t.matInv.m[2][1] * v.z;
        z = t.matInv.m[0][2] * v.x + t.matInv.m[1][2] * v.y + t.matInv.m[2][2] * v.z;
    }
    else {
        x = t.mat.m[0][0] * v.x + t.mat.m[0][1] * v.y + t.mat.m[0][2] * v.z;
        y = t.mat.m[1][0] * v.x + t.mat.m[1][1] * v.y + t.mat.m[1][2] * v.z;
        z = t.mat.m[2][0] * v.x + t.mat.m[2][1] * v.y + t.mat.m[2][2] * v.z;
    }

    return Point3Init(x, y, z);
}

inline Ray TransformRay(Transform t, Ray ray) {
    ray.origin = TransformPoint3(t, ray.origin);
    ray.dir = TransformVector3(t, ray.dir, false);
    return ray;
}

inline void TransformDoPoint3(Transform t, Point3 *p) {
#ifndef NODEBUG
    if (p == NULL) {
        assert(false);
        return;
    }
#endif
    *p = TransformPoint3(t, *p);
}

inline void TransformDoVector3(Transform t, Vector3 *v, bool isNormal) {
#ifndef NODEBUG
    if (v == NULL) {
        assert(false);
        return;
    }
#endif
    *v = TransformVector3(t, *v, isNormal);
}

inline void TransformDoRay(Transform t, Ray *ray) {
#ifndef NODEBUG
    if (ray == NULL) {
        assert(false);
        return;
    }
#endif
    *ray = TransformRay(t, *ray);
}
