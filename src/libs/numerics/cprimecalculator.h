#pragma once

// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "numerics/csieve.h"

// ================================================================================================
// Class to aid in finding / using prime numbers
// ================================================================================================
class CPrimeCalculator {

protected:

    CSieve sieve;
    uint32 currsieve;
    uint64 currnum;
    uint64 currsqrt;
    uint32 primealloc;
    uint64* primes;
    uint32 primecount;

public:

    // -- constructor / destructor
    CPrimeCalculator();
    ~CPrimeCalculator();

    // -- do one more interation of the sieve
    void CheckNext();

    // -- iterate until we find all the primes less than/equal to a given max
    void FindPrimesUpTo(uint64 max);

    // -- accessors
    uint64 NumPrimes();
    uint64 Prime(uint64 idx);
};

// ================================================================================================
// Calculate all the primes up to (and possibly including) the given maximum number
// ================================================================================================
inline void CPrimeCalculator::FindPrimesUpTo(uint64 max) {
    while(currnum < max)
        CheckNext();
}

// ================================================================================================
// Accessors
// ================================================================================================
inline uint64 CPrimeCalculator::NumPrimes() {
    return primecount;
}

inline uint64 CPrimeCalculator::Prime(uint64 idx) {
    return primes[idx];
}

