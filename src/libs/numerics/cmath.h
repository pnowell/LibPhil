#pragma once

// -- libs includes
#include "core/types.h"

// -- system includes
#include <math.h>

// ================================================================================================
// Class with various static utility math functions
// ================================================================================================
class CMath {

public:

    // -- square root
    static real32 Sqrt(real32 n);
    static real64 Sqrt(real64 n);

    // -- integer square root, yields the floor of the real valued sqrt(n)
    static uint32 ISqrt(uint32 n);
    static uint64 ISqrt(uint64 n);

    // -- convert a string representation of a number to a number
    static nint AToI(cpointer a);
};

// ================================================================================================
// Real square root functions
// ================================================================================================
inline real32 CMath::Sqrt(real32 n) {
    return ::sqrtf(n);
}

inline real64 CMath::Sqrt(real64 n) {
    return ::sqrt(n);
}

// ================================================================================================
// Integer square root
// ================================================================================================
inline uint32 CMath::ISqrt(uint32 n) {
    uint32 result = 0;
    int32 diff = n;

    while(diff != 0) {
        result += diff;
        diff = int32(n/result - result - 1) / 2;
    };

    return result;
}

inline uint64 CMath::ISqrt(uint64 n) {
    uint64 result = 0;
    int64 diff = n;

    while(diff != 0) {
        result += diff;
        diff = int64(n/result - result - 1) / 2;
    };

    return result;
}

