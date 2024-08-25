// test_array3.c

#include <stdio.h>
#include <stddef.h>
#include "../base/array3.h"
#include "../base/vector3.h"
#include "../base/point3.h"

void print3(Array3 a) {
    printf("%.3f %.3f %.3f\n", a.x, a.y, a.z);
}

int main() {
    Vector3 v1, v2;
    Point3 p1, p2;
    p1 = Point3Init(1,2,3);
    p2 = Point3Init(4,5,6);
    v1 = Vector3Init(1,1,1);
    v2 = Vector3Init(2,2,2);
    Point3DoPermute(&p1, 2, 0, 1);
    print3(p1);
    printf("%.3f\n", Point3NthItem(p1, 0));
    printf("%.3f\n", Point3NthItem(p1, 1));
    printf("%.3f\n", Point3NthItem(p1, 2));
    print3(Vector3Minus(v2, v1));
    Vector3DoMinus(&v2, (Vector3)p2);
    print3((Point3)v2);
    return 0;
}
