// spectrum.h

#ifndef _SPECTRUM_H_ // _SPECTRUM_H_
#define _SPECTRUM_H_

#include <stdbool.h>

typedef struct Spectrum {
    double r;
    double g;
    double b;
} Spectrum;


// Spectrum Constructor
inline Spectrum SpectrumInit(double r, double g, double b);

// Spectrum New Constructor
inline Spectrum * SpectrumNew(double r, double g, double b);

// Spectrum Deconstructor
inline void SpectrumFree(Spectrum *this, bool freeThis);


inline bool SpectrumIsBlack(Spectrum s);


inline double SpectrumGetR(Spectrum *this);

inline double SpectrumGetG(Spectrum *this);

inline double SpectrumGetB(Spectrum *this);


inline Spectrum SpectrumAdd(Spectrum a, Spectrum b);

inline Spectrum SpectrumMinus(Spectrum a, Spectrum b);

inline Spectrum SpectrumMix(Spectrum a, Spectrum b);

inline Spectrum SpectrumMul(Spectrum s, double n);

inline Spectrum SpectrumDiv(Spectrum s, double n);


inline void SpectrumDoAdd(Spectrum *this, Spectrum s);

inline void SpectrumDoMinus(Spectrum *this, Spectrum s);

inline void SpectrumDoMix(Spectrum *this, Spectrum s);

inline void SpectrumDoMul(Spectrum *this, double n);

inline void SpectrumDoDiv(Spectrum *this, double n);

#endif // _SPECTRUM_H_
