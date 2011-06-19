#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// Class with various static utility math functions
// ================================================================================================
class CMath {

public:

    // -- integer square root, yields the floor of the real valued sqrt(n)
    static nuint ISqrt(nuint n);

    // -- convert a string representation of a number to a number
    static nint AToI(cpointer a);
};

// ================================================================================================
// Integer square root
// ================================================================================================
inline nuint CMath::ISqrt(nuint n) {
    nuint result = 0;
    nint diff = n;

    while(diff != 0) {
        result += diff;
        diff = nint(n/result - result - 1) / 2;
    };

    return result;
}
