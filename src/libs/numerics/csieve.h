#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// Class for managing a sieve for more quickly searching for prime numbers
// ================================================================================================
class CSieve {

protected:

    nuint sievesize;
    nuint offsetsize;
    nuint* offsets;

public:

    CSieve();
    ~CSieve();

    // -- set up the sieve with the given primes
    void Prepare(nuint* primes, nuint count);

    // -- get an initial offset to move the given number onto a value we can iterate on
    // -- also return the offset index to start using when iterating
    nuint GetInitialOffset(nuint v, nuint& index);

    // -- accessors
    nuint NumOffsets();
    nuint Offset(nuint i);
};

// ================================================================================================
// Constructor
// ================================================================================================
inline CSieve::CSieve() : sievesize(0), offsets(NULL) {
}

// ================================================================================================
// Accessors
// ================================================================================================
inline nuint CSieve::NumOffsets() {
    return offsetsize;
}

inline nuint CSieve::Offset(nuint i) {
    return offsets[i];
}

