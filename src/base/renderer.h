// renderer.h

#ifndef _RENDERER_H_ // _RENDERER_H_
#define _RENDERER_H_

#include <stdbool.h>

#include "../base/scene.h"
#include "../image/image.h"

/* *** Renderer Interface Struct ***
 *
 * [Member]:
 * - void *rendererConfig: A pointer to the configuration parameter(s) of the actual renderer struct.
 * - Scene *scene: The scene which would be rendered.
 * 
 * [Method]:
 * - Image * Render(Renderer *this): Render the scene and take the pointer to an Image struct as output.
 * - void RendererFree(Renderer *this, bool freeThis): This method provides support to different deallocation strategies.
 */

typedef struct Renderer {
    void *rendererConfig;
    struct Scene *scene;
    struct Image * (* Render)(struct Renderer *this);
    void (* RendererFree)(struct Renderer *this, bool freeThis);
} Renderer;

// Note: The constructor and the deconstructor are implemented in the actual renderer struct.

#endif // _RENDERER_H_
