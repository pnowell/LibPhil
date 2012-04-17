// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/cmemory.h"
#include "io/clog.h"
#include "numerics/cprimecalculator.h"

// -- constants
static const nuint kPrimeAlloc = 1024;

// ================================================================================================
// Constructor
// ================================================================================================
CPrimeCalculator::CPrimeCalculator() : sieve(), primes(kPrimeAlloc) {
    // -- start the primes off with all the primes up to 30
    primes.Grow(2);
    primes.Grow(3);
    primes.Grow(5);
    primes.Grow(7);
    primes.Grow(11);
    primes.Grow(13);
    primes.Grow(17);
    primes.Grow(19);
    primes.Grow(23);
    primes.Grow(29);

    // -- what's the next number we should check
    currnum = 30;
    currsqrt = 6;

    // -- initialize the sieve
    sieve.Prepare(primes.GetElem(0), 5);
    currnum += sieve.GetInitialOffset(currnum, currsieve);
}

// ================================================================================================
// Destructor
// ================================================================================================
CPrimeCalculator::~CPrimeCalculator() {
}

// ================================================================================================
// Check the next possible prime
// ================================================================================================
void CPrimeCalculator::CheckNext() {
    // -- update the square root of the current number
    while(currsqrt * currsqrt <= currnum)
        ++currsqrt;

    nflag isprime = true;
    for(nuint i = 0; primes[i] <= currsqrt; ++i) {
        if((currnum % primes[i]) == 0) {
            isprime = false;
            break;
        }
    }

    // -- add it to the list of primes, if necessary
    if(isprime)
        primes.Grow(currnum);

    // -- move on to the next number to check, and update our position in the sieve iterator
    currnum += sieve.Offset(currsieve);
    ++currsieve;
    if(currsieve == sieve.NumOffsets())
        currsieve = 0;
}

// ================================================================================================
// Do a binary search to see if the given number is prime
// ================================================================================================
nflag CPrimeCalculator::IsPrime(nuint p) {
    FindPrimesUpTo(p);
    nuint idx;
    return primes.Search<CompareBasicTypes<nuint> >(p, idx);
}

