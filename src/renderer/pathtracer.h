// pathtracer.h

#ifndef _PATHTRACER_H_ // _PATHTRACER_H_
#define _PATHTRACER_H_

#include <stdbool.h>

#include "../image/image.h"
#include "../base/renderer.h"
#include "../base/spectrum.h"

typedef struct PathTracerConfig {
    int samplePerPixel;
    int maxDepth;
    double russianRoulette;
} PathTracerConfig;

Renderer PathTracerInit(Scene *scene, int samplePerPixel, int maxDepth, double russianRoulette);

Renderer * PathTracerNew(Scene *scene, int samplePerPixel, int maxDepth, double russianRoulette);

void PathTracerFree(Renderer *this, bool freeThis);

Image * PathTracerRender(Renderer *this);

#endif // _PATHTRACER_H_
