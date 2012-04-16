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
    nuint currsieve;
    nuint currnum;
    nuint currsqrt;
    CTable<nuint> primes;

public:

    // -- constructor / destructor
    CPrimeCalculator();
    ~CPrimeCalculator();

    // -- do one more iteration of the sieve
    void CheckNext();

    // -- iterate until we find all the primes less than/equal to a given max
    void FindPrimesUpTo(nuint max);

    // -- accessors
    nuint NumPrimes();
    nuint Prime(nuint idx);
};

// ================================================================================================
// Calculate all the primes up to (and possibly including) the given maximum number
// ================================================================================================
inline void CPrimeCalculator::FindPrimesUpTo(nuint max) {
    while(currnum <= max)
        CheckNext();
}

// ================================================================================================
// Accessors
// ================================================================================================
inline nuint CPrimeCalculator::NumPrimes() {
    return primes.Count();
}

inline nuint CPrimeCalculator::Prime(nuint idx) {
    return primes[idx];
}

