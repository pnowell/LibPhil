// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"
#include "numerics/cfactorizer.h"
#include "io/clog.h"

// -- local includes
#include "euler.h"

// -- constants
static const uintn kLimit = 10000;
static const uintn kAnswer = 31626;

// ------------------------------------------------------------------------------------------------
// Calculate the some of all the proper divisors
// ------------------------------------------------------------------------------------------------
static uintn SumOfDivisors(uintn num, CPrimeCalculator& primecalc) {
    CTable<uintn> factors;
    CTable<uintn> divisors;
    CFactorizer::CollectFactors(num, primecalc, factors);
    CFactorizer::CollectDivisors(factors, divisors);

    uintn sum = 0;
    uintn numdivisors = divisors.Count();
    for(uintn i = 0; i < numdivisors-1; ++i)
        sum += divisors[i];

    return sum;
}

// ================================================================================================
// Problem 21
// ================================================================================================
sint32 Problem21() {
    // -- first set up a prime calculator and get all the primes up to half the limit
    CPrimeCalculator& primecalc = PrimeCalculator();

    primecalc.FindPrimesUpTo(kLimit);

    CTable<flagn> shouldskip;
    shouldskip.GrowMultiple(false, kLimit);

    // -- check every number up through the limit to see if it's part of an amicable pair
    // -- then add it (and possibly it's paired number) and mark the paired number so that
    // -- we skip it
    uintn sum = 0;
    for(uintn i = 2; i < kLimit; ++i) {
        if(shouldskip[i])
            continue;

        uintn factorsum = SumOfDivisors(i, primecalc);
        if(factorsum != i && factorsum != 1 && SumOfDivisors(factorsum, primecalc) == i) {
            sum += i;
            if(factorsum < kLimit) {
                sum += factorsum;
                shouldskip[factorsum] = true;
            }
        }
    }

    CLog::Write("The sum of amicable numbers less than " UintNFmt_ " is " UintNFmt_ "\n",
                kLimit, sum);

    Assert_(sum == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}

