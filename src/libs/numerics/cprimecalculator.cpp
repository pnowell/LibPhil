// -- system includes
#include <stdlib.h>
#include <stdio.h>

// -- libs includes
#include "numerics/cprimecalculator.h"

// -- constants
static const uint32 kPrimeAlloc = 1024;

// ================================================================================================
// Constructor
// ================================================================================================
CPrimeCalculator::CPrimeCalculator() : sieve() {
    // -- start the primes off with all the primes up to 30
    primealloc = kPrimeAlloc;
    primes = reinterpret_cast<uint64*>(malloc(primealloc * sizeof(uint64)));
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    primes[4] = 11;
    primes[5] = 13;
    primes[6] = 17;
    primes[7] = 19;
    primes[8] = 23;
    primes[9] = 29;
    primecount = 10;

    // -- what's the next number we should check
    currnum = 30;
    currsqrt = 6;

    // -- initialize the sieve
    sieve.Prepare(primes, 5);
    currnum += sieve.GetInitialOffset(currnum, currsieve);
}

// ================================================================================================
// Destructor
// ================================================================================================
CPrimeCalculator::~CPrimeCalculator() {
    if(primes != NULL)
        free(primes);
}

// ================================================================================================
// Check the next possible prime
// ================================================================================================
void CPrimeCalculator::CheckNext() {
    // -- update the square root of the current number
    while(currsqrt * currsqrt <= currnum)
        ++currsqrt;

    nflag isprime = true;
    for(uint64 i = 0; primes[i] <= currsqrt; ++i) {
        if((currnum % primes[i]) == 0) {
            isprime = false;
            break;
        }
    }

    // -- add it to the list of primes, if necessary
    if(isprime) {
        if(primecount == primealloc) {
            uint32 newprimealloc = primealloc + kPrimeAlloc;
            primes = reinterpret_cast<uint64*>(realloc(primes, newprimealloc * sizeof(uint64)));
            primealloc = newprimealloc;
        }

        primes[primecount] = currnum;
        ++primecount;
    }

    // -- move on to the next number to check, and update our position in the sieve iterator
    currnum += sieve.Offset(currsieve);
    ++currsieve;
    if(currsieve == sieve.NumOffsets())
        currsieve = 0;
}

