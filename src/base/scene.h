// scene.h

#ifndef _SCENE_H_ // _SCENE_H_
#define _SCENE_H_

#include <stdbool.h>

#include "object.h"
#include "light.h"
#include "camera.h"
#include "list.h"

typedef struct Scene {
    struct List *objects;
    struct List *lights;
    struct Camera *camera;
} Scene;


// Scene Constructor
Scene SceneInit(List *objects, List *lights, Camera *camera);

// Scene New Constructor
Scene * SceneNew(List *objects, List *lights, Camera *camera);

// Scene Deconstructor
void SceneFree(Scene *this, bool freeThis);


#endif // _SCENE_H_
