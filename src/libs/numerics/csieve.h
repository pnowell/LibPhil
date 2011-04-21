#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// Class for managing a sieve for more quickly searching for prime numbers
// ================================================================================================
class CSieve {

protected:

    uint32 sievesize;
    uint32 offsetsize;
    uint32* offsets;

public:

    CSieve();
    ~CSieve();

    // -- set up the sieve with the given primes
    void Prepare(uint64* primes, uint32 count);

    // -- get an initial offset to move the given number onto a value we can iterate on
    // -- also return the offset index to start using when iterating
    uint32 GetInitialOffset(uint64 v, uint32& index);

    // -- accessors
    uint32 NumOffsets();
    uint32 Offset(uint32 i);
};

// ================================================================================================
// Constructor
// ================================================================================================
inline CSieve::CSieve() : sievesize(0), offsets(NULL) {
}

// ================================================================================================
// Accessors
// ================================================================================================
inline uint32 CSieve::NumOffsets() {
    return offsetsize;
}

inline uint32 CSieve::Offset(uint32 i) {
    return offsets[i];
}

