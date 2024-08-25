// utils.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "utils.h"

inline bool SolveQuadraticEquation(double a, double b, double c, double *x1, double *x2) {
    double delta;
    delta = b * b - 4 * a * c;
    if (delta < 0) {
        return false;
    }
    *x1 = (-b - sqrt(delta)) / (2 * a);
    *x2 = (-b + sqrt(delta)) / (2 * a);
    return true;
}

inline double ArcTan2(double y, double x) {
    double res = atan2(y, x);
    return res >= 0 ? res : res + 2 * PI;
}
