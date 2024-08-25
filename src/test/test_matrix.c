// test_matrix.c

#include <stdio.h>
#include <stddef.h>
#include "../base/matrix.h"

void printMat(Mat4x4 mat) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.3f ", mat.m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Mat4x4 mat, matInv;
    mat = Mat4x4Init(2, 1, 0, 3,
                     5, 8, 3, 2,
                     4, 2, 7, 1,
                     3, 1, 3, 4);
    printMat(mat);
    matInv = Mat4x4Inverse(mat);
    printMat(matInv);
    return 0;
}
