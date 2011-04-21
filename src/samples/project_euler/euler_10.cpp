// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "numerics/cprimecalculator.h"

// -- consts
static const uint64 maxprime = 2000000;

// ================================================================================================
// Find the sum of all primes less than 2 million
// ================================================================================================
int32 Problem10() {
    uint64 i;

    // -- set up the prime calculator and calculate all the primes up to the limit
    CPrimeCalculator primecalc;
    primecalc.FindPrimesUpTo(maxprime);
    uint64 numprimes = primecalc.NumPrimes();
    uint64 sum = 0;
    for(i = 0; i < numprimes; ++i) {
        uint64 currprime = primecalc.Prime(i);
        if(currprime >= maxprime)
            break;
        sum += currprime;
    }

    printf("The sum of all primes less than %lld is %lld\n", maxprime, sum);

    return 0;
}
