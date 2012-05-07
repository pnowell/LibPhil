#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// Class for managing a sieve for more quickly searching for prime numbers
// ================================================================================================
class CSieve {

protected:

    uintn sievesize;
    uintn offsetsize;
    uintn* offsets;

public:

    CSieve();
    ~CSieve();

    // -- set up the sieve with the given primes
    void Prepare(uintn* primes, uintn count);

    // -- get an initial offset to move the given number onto a value we can iterate on
    // -- also return the offset index to start using when iterating
    uintn GetInitialOffset(uintn v, uintn& index);

    // -- accessors
    uintn NumOffsets();
    uintn Offset(uintn i);
};

// ================================================================================================
// Constructor
// ================================================================================================
inline CSieve::CSieve() : sievesize(0), offsets(NULL) {
}

// ================================================================================================
// Accessors
// ================================================================================================
inline uintn CSieve::NumOffsets() {
    return offsetsize;
}

inline uintn CSieve::Offset(uintn i) {
    return offsets[i];
}

