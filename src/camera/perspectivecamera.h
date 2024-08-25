// perspectivecamera.h

#ifndef _PERSPECTIVECAMERA_H_ // _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include <stdbool.h>

#include "../base/camera.h"
#include "../base/sampler.h"
#include "../base/transform.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/ray.h"

typedef struct PerspectiveCameraData {
    Transform ndc2cam;
    Transform cam2ndc;
    double fov;
    double near;
    double far;
    double focalLength;
    double lenRadius;
} PerspectiveCameraData;


// PerspectiveCamera Constructor
Camera PerspectiveCameraInit(Point3 pos,
                             Point3 look,
                             Vector3 up,
                             int screenWidth, 
                             int screenHeight, 
                             double fov, 
                             double near, 
                             double far,
                             double focalLength,
                             double lenRadius);

// PerspectiveCamera New Constructor
Camera * PerspectiveCameraNew(Point3 pos,
                              Point3 look,
                              Vector3 up,
                              int screenWidth, 
                              int screenHeight, 
                              double fov, 
                              double near, 
                              double far,
                              double focalLength,
                              double lenRadius);

// PerspectiveCamera Deconstructor
void PerspectiveCameraFree(Camera *this, bool freeThis);


Ray PerspectiveCameraGenerateSample(Camera *this, int x, int y, Sampler *sampler);

#endif // _PERSPECTIVECAMERA_H_
