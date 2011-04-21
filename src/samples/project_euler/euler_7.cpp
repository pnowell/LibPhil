// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "numerics/cprimecalculator.h"

// -- consts
static const uint64 whichprime = 10001;

// ================================================================================================
// Find the 10001st prime number
// ================================================================================================
int32 Problem7() {
    CPrimeCalculator primecalc;
    while(primecalc.NumPrimes() < whichprime)
        primecalc.CheckNext();
    printf("The %lld prime is %lld\n", whichprime, primecalc.Prime(whichprime-1));

    return 0;
}

