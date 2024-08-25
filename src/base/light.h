// light.h

#ifndef _LIGHT_H_ // _LIGHT_H_
#define _LIGHT_H_

#include <stdbool.h>

#include "sampler.h"
#include "spectrum.h"
#include "point3.h"
#include "vector3.h"

/* *** Light Interface Struct ***
 *
 * [Member]:
 * - void *lightData: A pointer to the descriptive data or parameter(s) that are used to represent this Light.
 * - LightType type: An enum value which indicates the type of this Light.
 * 
 * [Method]:
 * - Spectrum GetLightSample(Light *this, Point3 *p, double *pdf): Randomly sample a point on the light and returns the radiance, the position, and the PDF of that point.
 * - Spectrum GetSpectrum(Light *this): **Only available for Area Light.** Returns the spectrum of this Light.
 * - Spectrum GetSpectrumByDir(Light *this, Vector3 dir): **Only available for Infinite Area Light.** Returns the spectrum of this Light in the given direction.
 * - void LightFree(Light *this, bool freeThis): This method provides support to different deallocation strategies.
 */

typedef enum LightType {
    DeltaPosition, DeltaDirection, Area, InfiniteArea
} LightType;

typedef struct Light {
    void *lightData;
    enum LightType type;
    struct Spectrum (* GetLightSample)(struct Light *this, Point3 *p, double *pdf, struct Sampler *sampler);
    struct Spectrum (* GetSpectrum)(struct Light *this);
    struct Spectrum (* GetSpectrumByDir)(struct Light *this, Vector3 dir);
    void (* LightFree)(struct Light *this, bool freeThis);
} Light;

// Note: The constructor and the deconstructor are implemented in the actual light struct.

#endif // _LIGHT_H_
