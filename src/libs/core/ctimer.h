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
    nreal GetSeconds() const;
    nuint GetMicro() const;

    // -- direct accessors
    nuint GetStart() const;
    nuint GetStop() const;
    nuint GetCycles() const;
    nuint GetFrequency() const;
};

// ================================================================================================
// Accessors
// ================================================================================================
inline nreal CTimer::GetSeconds() const {
    return (stop - start) / nreal(freq);
}

inline nuint CTimer::GetMicro() const {
    real64 conv = 1000000.0 / real64(freq);
    return nuint((stop - start) * conv);
}

inline nuint CTimer::GetStart() const {
    return start;
}

inline nuint CTimer::GetStop() const {
    return stop;
}

inline nuint CTimer::GetCycles() const {
    return stop - start;
}

inline nuint CTimer::GetFrequency() const {
    return freq;
}
