// main.c

#include <stdio.h>
#include <math.h>

// Include base struct.
#include "../base/scene.h"
#include "../base/light.h"
#include "../base/list.h"
#include "../base/shape.h"
#include "../base/transform.h"
#include "../base/point3.h"
#include "../base/vector3.h"
#include "../base/spectrum.h"
#include "../base/material.h"

// Include Image struct.
#include "../image/image.h"

// Include camera struct.
#include "../camera/perspectivecamera.h"

// Include light struct.
#include "../light/pointlight.h"
#include "../light/arealight.h"
#include "../light/infinitearealight.h"

// Include material struct.
#include "../material/lambertian.h"

// Include renderer struct.
#include "../renderer/pathtracer.h"

// Include shape struct.
#include "../shape/sphere.h"

int main() {
    Image *hdri, *image;
    Scene *scene;
    Renderer *renderer;
    Camera *camera;
    List *objects;
    List *lights;
    float *pixel;

    objects = ListNew(sizeof(Object));
    AddListItem(objects, ObjectNew(
                SphereNew(1, TransformGenerateTranslate(Point3Init(0, 0, 0))),
                NULL,
                LambertianNew(SpectrumInit(1, 1, 1))
                ));
    AddListItem(objects, ObjectNew(
                SphereNew(1000, TransformGenerateTranslate(Point3Init(0, 0, -1000))),
                NULL,
                LambertianNew(SpectrumInit(1, 1, 1))
                ));

    lights = ListNew(sizeof(Light));
    hdri = ImageNew(100, 100, RGB, HDR);
    int i, j;
    ImageForeachPixel(hdri, &i, &j, pixel, float) {
        pixel[0] = (float)j / 100;
        pixel[1] = (float)j / 100;
        pixel[2] = 1 - (float)j / 100;
    }
    AddListItem(lights, InfiniteAreaLightNew(hdri));

    camera = PerspectiveCameraNew(Point3Init(5, 5, 5),  // Point3 pos
                                  Point3Init(0, 0, 0),  // Point3 look
                                  Vector3Init(0, 0, 1), // Vector3 up
                                  640,                  // int screenWidth
                                  360,                  // int screenHeight
                                  60,                   // double fov
                                  0.001,                // double near
                                  10000,                // double far
                                  4 * sqrt(3),          // double focalLength
                                  0.2);                 // double lenRadius

    scene = SceneNew(objects, lights, camera);
    renderer = PathTracerNew(scene, 100, 100, 0.8);
    image = renderer->Render(renderer);
    ImageSave(image, "render.png", PNG);
    renderer->RendererFree(renderer, true);
    ImageFree(image, true);
    return 0;
}
