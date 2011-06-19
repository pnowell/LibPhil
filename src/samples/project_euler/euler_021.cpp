// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"
#include "numerics/cfactorizer.h"
#include "io/clog.h"

// -- constants
static const nuint kLimit = 10000;
static const nuint kAnswer = 31626;

// ------------------------------------------------------------------------------------------------
// Calculate the some of all the proper divisors
// ------------------------------------------------------------------------------------------------
static nuint SumOfDivisors(nuint num, CPrimeCalculator& primecalc) {
    CTable<nuint> factors;
    CTable<nuint> divisors;
    CFactorizer::CollectFactors(num, primecalc, factors);
    CFactorizer::CollectDivisors(factors, divisors);

    nuint sum = 0;
    nuint numdivisors = divisors.Count();
    for(nuint i = 0; i < numdivisors-1; ++i)
        sum += divisors[i];

    return sum;
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

    CLog::Write("The sum of amicable numbers less than " NUintFmt_ " is " NUintFmt_ "\n",
                kLimit, sum);

    Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}

