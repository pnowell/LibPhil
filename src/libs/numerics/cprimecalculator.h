#pragma once

// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "containers/ctable.h"
#include "numerics/csieve.h"

// ================================================================================================
// Class to aid in finding / using prime numbers
// ================================================================================================
class CPrimeCalculator {

protected:

    CSieve sieve;
    uintn currsieve;
    uintn currnum;
    uintn currsqrt;
    CTable<uintn> primes;

public:

    // -- constructor / destructor
    CPrimeCalculator();
    ~CPrimeCalculator();

    // -- do one more iteration of the sieve
    void CheckNext();

    // -- iterate until we find all the primes less than/equal to a given max
    void FindPrimesUpTo(uintn max);

    // -- accessors
    uintn NumPrimes();
    uintn Prime(uintn idx);
    flagn IsPrime(uintn p);
};

// ================================================================================================
// Calculate all the primes up to (and possibly including) the given maximum number
// ================================================================================================
inline void CPrimeCalculator::FindPrimesUpTo(uintn max) {
    while(currnum <= max)
        CheckNext();
}

// ================================================================================================
// Accessors
// ================================================================================================
inline uintn CPrimeCalculator::NumPrimes() {
    return primes.Count();
}

inline uintn CPrimeCalculator::Prime(uintn idx) {
    return primes[idx];
}

