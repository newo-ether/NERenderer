// matrix.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "matrix.h"
#include "utils.h"

inline Mat4x4 Mat4x4Init(double a00, double a01, double a02, double a03,
                         double a10, double a11, double a12, double a13,
                         double a20, double a21, double a22, double a23,
                         double a30, double a31, double a32, double a33) {
    Mat4x4 mat;
    mat.m[0][0] = a00; mat.m[0][1] = a01; mat.m[0][2] = a02; mat.m[0][3] = a03;
    mat.m[1][0] = a10; mat.m[1][1] = a11; mat.m[1][2] = a12; mat.m[1][3] = a13;
    mat.m[2][0] = a20; mat.m[2][1] = a21; mat.m[2][2] = a22; mat.m[2][3] = a23;
    mat.m[3][0] = a30; mat.m[3][1] = a31; mat.m[3][2] = a32; mat.m[3][3] = a33;
    return mat;
}

inline Mat4x4 * Mat4x4New(double a00, double a01, double a02, double a03,
                          double a10, double a11, double a12, double a13,
                          double a20, double a21, double a22, double a23,
                          double a30, double a31, double a32, double a33) {
    Mat4x4 *mat;
    mat = (Mat4x4 *)malloc(MAT_SIZE);
    mat->m[0][0] = a00; mat->m[0][1] = a01; mat->m[0][2] = a02; mat->m[0][3] = a03;
    mat->m[1][0] = a10; mat->m[1][1] = a11; mat->m[1][2] = a12; mat->m[1][3] = a13;
    mat->m[2][0] = a20; mat->m[2][1] = a21; mat->m[2][2] = a22; mat->m[2][3] = a23;
    mat->m[3][0] = a30; mat->m[3][1] = a31; mat->m[3][2] = a32; mat->m[3][3] = a33;
    return mat;
}

inline void Mat4x4Free(Mat4x4 *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline Mat4x4 Mat4x4GenerateIdentity() {
    Mat4x4 mat;
    mat.m[0][0] = 1; mat.m[0][1] = 0; mat.m[0][2] = 0; mat.m[0][3] = 0;
    mat.m[1][0] = 0; mat.m[1][1] = 1; mat.m[1][2] = 0; mat.m[1][3] = 0;
    mat.m[2][0] = 0; mat.m[2][1] = 0; mat.m[2][2] = 1; mat.m[2][3] = 0;
    mat.m[3][0] = 0; mat.m[3][1] = 0; mat.m[3][2] = 0; mat.m[3][3] = 1;
    return mat;
}

inline Mat4x4 Mat4x4Mul(Mat4x4 mat_a, Mat4x4 mat_b) {
    Mat4x4 mat_new;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat_new.m[i][j] = mat_a.m[i][0] * mat_b.m[0][j] +
                              mat_a.m[i][1] * mat_b.m[1][j] +
                              mat_a.m[i][2] * mat_b.m[2][j] +
                              mat_a.m[i][3] * mat_b.m[3][j];
        }
    }
    return mat_new;
}

inline Mat4x4 Mat4x4Transpose(Mat4x4 mat) {
    Mat4x4 mat_new;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat_new.m[i][j] = mat.m[j][i];
        }
    }
    return mat_new;
}

inline Mat4x4 Mat4x4Inverse(Mat4x4 mat) {
    Mat4x4 matInv;
    double aug[4][8];

    // Construct Augmented Matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            aug[i][j] = mat.m[i][j];
            if (i == j) {
                aug[i][j+4] = 1;
            }
            else {
                aug[i][j+4] = 0;
            }
        }
    }

#ifndef NODEBUG 
    // Print Augmented Matrix
    printf("\n\nAugmented Matrix:\n\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%.3f ", aug[i][j]);
        }
        printf("\n");
    }
    printf("\nStart Applying Gaussian Elimination...\n");
#endif

    // Apply Gaussian Elimination
    for (int i = 0; i < 4; i++) {
        if (EQUALTOZERO(aug[i][i], 6)) {
            int j = i + 1;
            for (; j < 4; j++) {
                if (!EQUALTOZERO(aug[j][i], 6)) {
                    break;
                }
            }
            if (j == 4) {
                assert(false);
                return Mat4x4GenerateIdentity();
            }

#ifndef NODEBUG
            printf("\n[%d][%d] == 0, swaping %d line and %d line...\n", i, i, i, j);
#endif

            for (int k = 0; k < 8; k++) {
                double tmp;
                tmp = aug[i][k];
                aug[i][k] = aug[j][k];
                aug[j][k] = tmp;
            }
        }
        for (int j = i + 1; j < 4; j++) {
            if (!EQUALTOZERO(aug[j][i], 6)) {
                double l = aug[j][i] / aug[i][i];
                for (int k = i; k < 8; k++) {
                    aug[j][k] -= l * aug[i][k];
                }
            }
        }

#ifndef NODEBUG
        // Print Current Matrix
        printf("\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%.3f ", aug[i][j]);
            }
            printf("\n");
        }
#endif
    }

#ifndef NODEBUG
    printf("\nStart Applying Back Substitusion...\n");
#endif

    // Apply Back Substitusion
    for (int i = 3; i >= 0; i--) {
        double Inv;
        if (EQUALTOZERO(aug[i][i], 6)) {
            assert(false);
            return Mat4x4GenerateIdentity();
        }
        Inv = 1.0 / aug[i][i];
        for (int k = i; k < 8; k++) {
            aug[i][k] *= Inv;
        }
        for (int j = i - 1; j >= 0; j--) {
            if (aug[j][i] != 0) {
                double l = aug[j][i];
                for (int k = i; k < 8; k++) {
                    aug[j][k] -= l * aug[i][k];
                }
            }
        }

#ifndef NODEBUG
        // Print Current Matrix
        printf("\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%.3f ", aug[i][j]);
            }
            printf("\n");
        }
#endif
    }

#ifndef NODEBUG
    printf("\nResult Matrix:\n");
#endif

    // Extract the Result Matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matInv.m[i][j] = aug[i][j + 4];
        }
    }

#ifndef NODEBUG
        // Print Current Matrix
        printf("\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                printf("%.3f ", matInv.m[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
#endif

    return matInv;
}

inline void Mat4x4DoLeftMul(Mat4x4 *this, Mat4x4 mat) {
    Mat4x4 mat_new;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat_new.m[i][j] = mat.m[i][0] * this->m[0][j] +
                              mat.m[i][1] * this->m[1][j] +
                              mat.m[i][2] * this->m[2][j] +
                              mat.m[i][3] * this->m[3][j];
        }
    }
    memcpy(this, &mat_new, MAT_SIZE);
}

inline void Mat4x4DoRightMul(Mat4x4 *this, Mat4x4 mat) {
    Mat4x4 mat_new;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat_new.m[i][j] = this->m[i][0] * mat.m[0][j] +
                              this->m[i][0] * mat.m[1][j] +
                              this->m[i][0] * mat.m[2][j] +
                              this->m[i][0] * mat.m[3][j];
        }
    }
    memcpy(this, &mat_new, MAT_SIZE);
}

inline void Mat4x4DoTranspose(Mat4x4 *this) {
    Mat4x4 mat_new;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat_new.m[i][j] = this->m[j][i];
        }
    }
    memcpy(this, &mat_new, MAT_SIZE);
}
