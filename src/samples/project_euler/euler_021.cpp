// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"

// -- constants
static const nuint kLimit = 10000;
static const nuint kAnswer = 31626;

// ------------------------------------------------------------------------------------------------
// Recursive function to sum all the combinations of factors
// ------------------------------------------------------------------------------------------------
static void SumFactorCombinations(CTable<nuint>& factor, nuint curr, nuint prod, nuint& sum) {
    nuint factorcount = factor.Count();
    nuint f = factor[curr];

    // -- look for the upper bound of the same factor
    nuint end = curr;
    while(end < factorcount && factor[end] == f)
        ++end;

    // -- figure out if we're the end of the line and so we should be adding into the sum
    nflag record = end == factorcount;

    // -- loop over the number of times this factor is repeated and deal with all of them
    for(nuint i = curr; i <= end; ++i) {
        if(record)
            sum += prod;
        else
            SumFactorCombinations(factor, end, prod, sum);

        prod *= f;
    }
}

// ------------------------------------------------------------------------------------------------
// Calculate the some of all the proper divisors
// ------------------------------------------------------------------------------------------------
static nuint SumOfDivisors(nuint num, CPrimeCalculator& primecalc) {
    // -- make sure the prime calculator has enough primes
    primecalc.FindPrimesUpTo(num);

    // -- get the prime factorization of the number
    CTable<nuint> factor;
    nuint leftover = num;
    nuint numprimes = primecalc.NumPrimes();
    for(nuint i = 0; i < numprimes && leftover > 1; ++i) {
        nuint currprime = primecalc.Prime(i);
        while((leftover % currprime) == 0) {
            leftover /= currprime;
            factor.Grow(currprime);
        }
    }
    Assert_(leftover == 1, "We weren't able to find all the factors of " NUintFmt_, num);

    // -- handle primes specially (since they shouldn't be considered their own divisor)
    if(factor[0] == num)
        return 1;

    // -- iterate through all the possible unique combinations of factors and combine them
    // -- into the unique proper divisors and sum them all up
    nuint result = 0;
    SumFactorCombinations(factor, 0, 1, result);
    // -- this will have also added in the number itself as a divisor, so subtract that out
    return result - num;
}

// ================================================================================================
// Problem 21
// ================================================================================================
int32 Problem21() {
    // -- first set up a prime calculator and get all the primes up to half the limit
    CPrimeCalculator primecalc;
    primecalc.FindPrimesUpTo(kLimit);

    CTable<nflag> shouldskip;
    shouldskip.GrowMultiple(false, kLimit);

    // -- check every number up through the limit to see if it's part of an amicable pair
    // -- then add it (and possibly it's paired number) and mark the paired number so that
    // -- we skip it
    nuint sum = 0;
    for(nuint i = 2; i < kLimit; ++i) {
        if(shouldskip[i])
            continue;

        nuint factorsum = SumOfDivisors(i, primecalc);
        if(factorsum != i && factorsum != 1 && SumOfDivisors(factorsum, primecalc) == i) {
            sum += i;
            if(factorsum < kLimit) {
                sum += factorsum;
                shouldskip[factorsum] = true;
            }
        }
    }

    printf("The sum of amicable numbers less than " NUintFmt_ " is " NUintFmt_ "\n", kLimit, sum);

    Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}

