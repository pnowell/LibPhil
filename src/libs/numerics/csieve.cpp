// -- system includes
#include <stdlib.h>

// -- libs includes
#include "numerics/csieve.h"

// ================================================================================================
// Destructor
// ================================================================================================
CSieve::~CSieve() {
    if(offsets != NULL)
        free(offsets);
}

// ================================================================================================
// Prepare the sieve with a list of primes
// ================================================================================================
void CSieve::Prepare(uint64* primes, uint32 count) {
    uint32 i;

    sievesize = 1;
    for(i = 0; i < count; ++i)
        sievesize *= uint32(primes[i]);

    // -- temporarily allocate that much memory and store it
    pointer sieve = reinterpret_cast<pointer>(calloc(sievesize, sizeof(char)));

    // -- go through and mark all the multiples of the given
    for(i = 0; i < count; ++i) {
        uint32 prime = uint32(primes[i]);
        uint32 lim = sievesize / prime;
        for(uint32 j = 1; j <= lim; ++j)
            sieve[j*prime-1] = 1;
    }

    // -- now count the number of zeros
    offsetsize = 0;
    for(i = 0; i < sievesize; ++i)
        offsetsize += 1-sieve[i];

    // -- now we need to allocate that many offsets
    if(offsets != NULL)
        free(offsets);
    offsets = reinterpret_cast<uint32*>(malloc(offsetsize * sizeof(uint32)));

    // -- now walk through the sieve again and record all the offsets
    uint32 curroffset = 0;
    uint32 offsetvalue = 1;
    for(i = 1; i < sievesize && curroffset < offsetsize; ++i) {
        if(sieve[i] == 1)
            ++offsetvalue;
        else {
            offsets[curroffset] = offsetvalue;
            ++curroffset;
            offsetvalue = 1;
        }
    }

    // -- add the remaining to the first offset (so that the sieve naturally wraps)
    offsets[offsetsize - 1] = offsetvalue;

    // -- free our temporary memory
    free(sieve);
}

// ================================================================================================
// Get the initial offset you need to start using a sieve
// ================================================================================================
uint32 CSieve::GetInitialOffset(uint64 v, uint32& index) {
    // -- reduce the value to its offset from the beginning of the sieve
    uint32 remainder = uint32(v % sievesize);

    // -- handle the 0 and 1 case specially
    if(remainder == 0 || remainder == 1) {
        index = 0;
        return 1 - remainder;
    }

    // -- otherwise subtract out the implicit one
    --remainder;

    // -- for each index
    for(index = 1; index < offsetsize; ++index) {
        // -- check to see if the remainder is less than the last index
        if(remainder <= offsets[index-1])
            return offsets[index-1] - remainder;

        // -- otherwise decrement it and move on
        remainder -= offsets[index-1];
    }

    // -- if we made it out here, the remainder is within the last offset
    index = 0;
    return offsets[index] - remainder;
}

