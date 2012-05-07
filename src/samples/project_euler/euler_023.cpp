// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"
#include "numerics/cfactorizer.h"
#include "io/clog.h"

// -- local includes
#include "euler.h"

// -- constants
static const uintn kLimit = 28123;
static const uintn kAnswer = 4179871;

// ================================================================================================
// Problem 23
// ================================================================================================
int32 Problem23() {
    // -- we'll keep a table of flags that says if any number can be the sum of abundant numbers
    CTable<nflag> issum;
    issum.GrowMultiple(false, kLimit);

    // -- first build a table of abundant numbers
    CTable<uintn> abundant;
    CPrimeCalculator& primecalc = PrimeCalculator();
    CTable<uintn> factors;
    CTable<uintn> divisors;
    for(uintn i = 2; i < kLimit; ++i) {
        CFactorizer::CollectFactors(i, primecalc, factors);
        CFactorizer::CollectDivisors(factors, divisors);

        // -- add all the divisors, except for the last one (which is the number itself)
        uintn numdivisors = divisors.Count();
        uintn divisorsum = 0;
        for(uintn j = 0; j < numdivisors - 1 && divisorsum <= i; ++j)
            divisorsum += divisors[j];

        // -- if we have an abundant number
        if(divisorsum > i) {
            // -- add it to the list
            abundant.Grow(i);

            // -- combine it with every abundant number (including itself) to cross off
            // -- candidates in the issum table
            uintn numabundant = abundant.Count();
            for(uintn j = 0; j < numabundant; ++j) {
                uintn sum = i + abundant[j];
                if(sum < kLimit)
                    issum[sum] = true;
            }
        }
    }

    // -- finally go through the list of flags and sum all the ones that are still false
    uintn result = 0;
    for(uintn i = 0; i < kLimit; ++i) {
        if(!issum[i])
            result += i;
    }

    CLog::Write("The sum of all numbers that can't be written\n"
                "as a sum of two abundant numbers is " NUintFmt_ "\n", result);

    Assert_(result == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
