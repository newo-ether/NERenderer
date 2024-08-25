// test_camera.c

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../base/camera.h"
#include "../camera/perspectivecamera.h"
#include "../base/sampler.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/utils.h"
#include "../base/ray.h"

int main() {
    Camera camera;
    Sampler sampler;
    Point3 pMin, pMax;
    Ray ray;
    bool passOrigin;

    camera = PerspectiveCameraInit(Point3Init(1, 1, 1),     // Point3 pos
                                   Point3Init(0, 0, 0),     // Point3 look
                                   Vector3Init(0, 0, 1),    // Vector3 up
                                   1920,                    // int screenWidth
                                   1080,                    // int screenHeight
                                   60,                      // double fov
                                   0.001,                   // double near
                                   10000,                   // double far
                                   sqrt(3),                 // double focalLength
                                   0.2);                    // double lenRadius

    sampler = SamplerInit(time(NULL));
    ray = camera.GenerateSample(&camera, 960, 540, &sampler);
    pMin = RayGetPoint(&ray, ray.tMin);
    pMax = RayGetPoint(&ray, ray.tMax);
    passOrigin = EQUAL3(Vector3Neg(ray.origin).x / ray.dir.x,
                        Vector3Neg(ray.origin).y / ray.dir.y,
                        Vector3Neg(ray.origin).z / ray.dir.z,
                        4);
    printf("Origin: [%.3f, %.3f, %.3f]\n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf("Direction: [%.3f, %.3f, %.3f]\n", ray.dir.x, ray.dir.y, ray.dir.z);
    printf("tMin: %.3f\n", ray.tMin);
    printf("tMax: %.3f\n", ray.tMax);
    printf("pMin: [%.3f, %.3f, %.3f]\n", pMin.x, pMin.y, pMin.z);
    printf("pMax: [%.3f, %.3f, %.3f]\n", pMax.x, pMax.y, pMax.z);
    printf("passOrigin: %s\n", passOrigin ? "true" : "false");
    PerspectiveCameraFree(&camera, false);
    return 0;
}
