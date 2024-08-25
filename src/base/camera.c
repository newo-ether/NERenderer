// camera.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include "camera.h"

inline int CameraGetScreenWidth(Camera *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->screenWidth;
}

inline int CameraGetScreenHeight(Camera *this) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return 0;
    }
#endif
    return this->screenHeight;
}
