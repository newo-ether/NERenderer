// material.h

#ifndef _MATERIAL_H_ // _MATERIAL_H_
#define _MATERIAL_H_

#include <stdbool.h>

#include "spectrum.h"
#include "vector3.h"

/* *** Material Interface Struct ***
 *
 * [Member]:
 * - void *materialData: A pointer to the descriptive data or parameter(s) that are used to represent this Material.
 * 
 * [Method]:
 * - Spectrum BSDF(Material *this, Vector3 wi, Vector3 wo, Vector3 normal): The BSDF of the given Material.
 * - void MaterialFree(Material *this, bool freeThis): This method provides support to different deallocation strategies.
 */

typedef struct Material {
    void *materialData;
    struct Spectrum (* BSDF)(struct Material *this, Vector3 wi, Vector3 wo, Vector3 normal);
    void (* MaterialFree)(struct Material *this, bool freeThis);
} Material;

// Note: The constructor and the deconstructor are implemented in the actual material struct.

#endif // _MATERIAL_H_
