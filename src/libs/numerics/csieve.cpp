// -- libs includes
#include "core/cmemory.h"
#include "core/utils.h"
#include "numerics/csieve.h"

// ================================================================================================
// Destructor
// ================================================================================================
CSieve::~CSieve() {
    if(offsets != NULL)
        CMemory::Free(offsets);
}

// ================================================================================================
// Prepare the sieve with a list of primes
// ================================================================================================
void CSieve::Prepare(nuint* primes, nuint count) {
    nuint i;

    sievesize = 1;
    for(i = 0; i < count; ++i)
        sievesize *= nuint(primes[i]);

    // -- temporarily allocate that much memory and store it
    pointer sieve = recast_<pointer>(CMemory::CAlloc(sievesize));

    // -- go through and mark all the multiples of the given
    for(i = 0; i < count; ++i) {
        nuint prime = nuint(primes[i]);
        nuint lim = sievesize / prime;
        for(nuint j = 1; j <= lim; ++j)
            sieve[j*prime-1] = 1;
    }

    // -- now count the number of zeros
    offsetsize = 0;
    for(i = 0; i < sievesize; ++i)
        offsetsize += 1-sieve[i];

    // -- now we need to allocate that many offsets
    if(offsets != NULL)
        CMemory::Free(offsets);
    offsets = recast_<nuint*>(CMemory::Alloc(offsetsize * sizeof(nuint)));

    // -- now walk through the sieve again and record all the offsets
    nuint curroffset = 0;
    nuint offsetvalue = 1;
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
    CMemory::Free(sieve);
}

// ================================================================================================
// Get the initial offset you need to start using a sieve
// ================================================================================================
nuint CSieve::GetInitialOffset(nuint v, nuint& index) {
    // -- reduce the value to its offset from the beginning of the sieve
    nuint remainder = nuint(v % sievesize);

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

