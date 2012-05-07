#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// A class for taking high precision timings
// ================================================================================================
class CTimer {

protected:

    uint64 start;
    uint64 stop;
    uint64 freq;
    uint64 mode;

public:

    // -- constructor (automatically starts)
    CTimer();

    // -- explicit start / stop
    void Start();
    void Stop();

    // -- accessors to timing information
    realn GetSeconds() const;
    uintn GetMicro() const;

    // -- direct accessors
    uintn GetStart() const;
    uintn GetStop() const;
    uintn GetCycles() const;
    uintn GetFrequency() const;
};

// ================================================================================================
// Accessors
// ================================================================================================
inline realn CTimer::GetSeconds() const {
    return (stop - start) / realn(freq);
}

inline uintn CTimer::GetMicro() const {
    real64 conv = 1000000.0 / real64(freq);
    return uintn((stop - start) * conv);
}

inline uintn CTimer::GetStart() const {
    return start;
}

inline uintn CTimer::GetStop() const {
    return stop;
}

inline uintn CTimer::GetCycles() const {
    return stop - start;
}

inline uintn CTimer::GetFrequency() const {
    return freq;
}
