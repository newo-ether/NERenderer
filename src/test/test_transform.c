// test_transform.c

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "../base/transform.h"
#include "../base/vector3.h"
#include "../base/point3.h"
#include "../base/ray.h"

void printTransform(Transform t, bool printInv) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.3f ", t.mat.m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    if (printInv) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                printf("%.3f ", t.matInv.m[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void print3(Array3 a) {
    printf("%.3f %.3f %.3f\n", a.x, a.y, a.z);
}

int main() {
    Transform t;
    Point3 p;
    Vector3 v;

    t = TransformGenerateTranslate(Vector3Init(-1, 2, 4));
    p = Point3Init(0, 1, 2);
    v = Vector3Init(1, 0, 0);
    printTransform(t, true);

    print3(p);
    p = TransformPoint3(t, p);
    print3(p);
    p = TransformPoint3(TransformInverse(t), p);
    print3(p);

    print3(v);
    t = TransformGenerateRotateZ(90);
    print3(TransformVector3(t, v, false));
    t = TransformGenerateRotate(Vector3Init(0, 0, 2), 90);
    print3(TransformVector3(t, v, false));

    return 0;
}
