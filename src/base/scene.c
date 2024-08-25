// scene.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>

#include "scene.h"
#include "object.h"
#include "light.h"
#include "camera.h"
#include "list.h"

Scene SceneInit(List *objects, List *lights, Camera *camera) {
    Scene scene;
    scene.objects = objects;
    scene.lights = lights;
    scene.camera = camera;
    return scene;
}

Scene * SceneNew(List *objects, List *lights, Camera *camera) {
    Scene *scene;
    scene = (Scene *)malloc(sizeof(Scene));
    scene->objects = objects;
    scene->lights = lights;
    scene->camera = camera;
    return scene;
}

void SceneFree(Scene *this, bool freeThis) {
    if (this == NULL) {
        return;
    }
    if (this->objects != NULL) {
        ListItem *item;
        ListForeachItem(this->objects, item) {
            Object *object = (Object *)(GetListItemContent(item));
            ObjectFree(object, true);
            ChangeListItem(this->objects, item, NULL);
        }
        ListFree(this->objects, true);
    }
    if (this->lights != NULL) {
        ListItem *item;
        ListForeachItem(this->lights, item) {
            Light *light = (Light *)(GetListItemContent(item));
            light->LightFree(light, true);
            ChangeListItem(this->objects, item, NULL);
        }
        ListFree(this->lights, true);
    }
    if (this->camera != NULL) {
        this->camera->CameraFree(this->camera, true);
    }
    if (freeThis) {
        free(this);
    }
}
