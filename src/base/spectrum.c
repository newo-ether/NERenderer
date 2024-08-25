// spectrum.c

#include "../config/config.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include "spectrum.h"

inline Spectrum SpectrumInit(double r, double g, double b) {
    Spectrum s;
    s.r = r;
    s.g = g;
    s.b = b;
    return s;
}

inline Spectrum * SpectrumNew(double r, double g, double b) {
    Spectrum *s;
    s = (Spectrum *)malloc(sizeof(Spectrum));
    s->r = r;
    s->g = g;
    s->b = b;
    return s;
}

inline void SpectrumFree(Spectrum *this, bool freeThis) {
    if (this != NULL && freeThis) {
        free(this);
    }
}

inline bool SpectrumIsBlack(Spectrum s) {
    if (s.r == 0.0 && s.g == 0.0 && s.b == 0.0) {
        return true;
    }
    else {
        return false;
    }
}

inline double SpectrumGetR(Spectrum *this) {
    if (this == NULL) {
        return 0;
    }
    return this->r;
}

inline double SpectrumGetG(Spectrum *this) {
    if (this == NULL) {
        return 0;
    }
    return this->g;
}

inline double SpectrumGetB(Spectrum *this) {
    if (this == NULL) {
        return 0;
    }
    return this->b;
}

inline Spectrum SpectrumAdd(Spectrum a, Spectrum b) {
    return SpectrumInit(a.r + b.r, a.g + b.g, a.b + b.b);
}

inline Spectrum SpectrumMinus(Spectrum a, Spectrum b) {
    return SpectrumInit(a.r - b.r, a.g - b.g, a.b - b.b);
}

inline Spectrum SpectrumMix(Spectrum a, Spectrum b) {
    return SpectrumInit(a.r * b.r, a.g * b.g, a.b * b.b);
}

inline Spectrum SpectrumMul(Spectrum s, double n) {
    return SpectrumInit(s.r * n, s.g * n, s.b * n);
}

inline Spectrum SpectrumDiv(Spectrum s, double n) {
    double invN = 1 / n;
    return SpectrumInit(s.r * invN, s.g * invN, s.b * invN);
}

inline void SpectrumDoAdd(Spectrum *this, Spectrum s) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->r += s.r;
    this->g += s.g;
    this->b += s.b;
}

inline void SpectrumDoMinus(Spectrum *this, Spectrum s) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->r -= s.r;
    this->g -= s.g;
    this->b -= s.b;
}

inline void SpectrumDoMix(Spectrum *this, Spectrum s) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->r *= s.r;
    this->g *= s.g;
    this->b *= s.b;
}

inline void SpectrumDoMul(Spectrum *this, double n) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    this->r *= n;
    this->g *= n;
    this->b *= n;
}

inline void SpectrumDoDiv(Spectrum *this, double n) {
#ifndef NODEBUG
    if (this == NULL) {
        assert(false);
        return;
    }
#endif
    double invN = 1 / n;
    this->r *= invN;
    this->g *= invN;
    this->b *= invN;
}
