// camera.h

#ifndef _CAMERA_H_ // _CAMERA_H_
#define _CAMERA_H_

#include <stdbool.h>

#include "ray.h"
#include "sampler.h"
#include "transform.h"

/* *** Camera Interface Struct ***
 *
 * [Member]:
 * - void *cameraData: A pointer to the descriptive data or parameter(s) that are used to represent this Camera.
 * - int screenWidth: The width of the screen.
 * - int screenHeight: The height of the screen.
 * - Transform cam2world: A transformation matrix from the camera space to the world space.
 * - Transform world2cam: A transformation matrix from the world space to the camera space.
 * - void CameraFree(Light *this, bool freeThis): This method provides support to different deallocation strategies.
 * 
 * [Method]:
 * - Ray GenerateSample(Camera *this, int x, int y, Sampler *sampler): Generate a ray sample of this Camera. the x and the y indicate the index of current pixel.
 * - void CameraFree(Camera *this, bool freeThis): This method provides support to different deallocation strategies.
 */

typedef struct Camera {
    void *cameraData;
    int screenWidth;
    int screenHeight;
    struct Transform cam2world;
    struct Transform world2cam;
    struct Ray (* GenerateSample)(struct Camera *this, int x, int y, struct Sampler *sampler);
    void (* CameraFree)(struct Camera *this, bool freeThis);
} Camera;

// Note: The constructor and the deconstructor are implemented in the actual camera struct.

inline int CameraGetScreenWidth(Camera *this);

inline int CameraGetScreenHeight(Camera *this);

#endif // _CAMERA_H_
