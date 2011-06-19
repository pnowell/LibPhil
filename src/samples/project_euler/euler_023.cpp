// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"
#include "numerics/cfactorizer.h"
#include "io/clog.h"

// -- constants
static const nuint kLimit = 28123;
static const nuint kAnswer = 4179871;

// ================================================================================================
// Problem 23
// ================================================================================================
int32 Problem23() {
    // -- we'll keep a table of flags that says if any number can be the sum of abundant numbers
    CTable<nflag> issum;
    issum.GrowMultiple(false, kLimit);

    // -- first build a table of abundant numbers
    CTable<nuint> abundant;
    CPrimeCalculator primecalc;
    CTable<nuint> factors;
    CTable<nuint> divisors;
    for(nuint i = 2; i < kLimit; ++i) {
        CFactorizer::CollectFactors(i, primecalc, factors);
        CFactorizer::CollectDivisors(factors, divisors);

        // -- add all the divisors, except for the last one (which is the number itself)
        nuint numdivisors = divisors.Count();
        nuint divisorsum = 0;
        for(nuint j = 0; j < numdivisors - 1 && divisorsum <= i; ++j)
            divisorsum += divisors[j];

        // -- if we have an abundant number
        if(divisorsum > i) {
            // -- add it to the list
            abundant.Grow(i);

            // -- combine it with every abundant number (including itself) to cross off
            // -- candidates in the issum table
            nuint numabundant = abundant.Count();
            for(nuint j = 0; j < numabundant; ++j) {
                nuint sum = i + abundant[j];
                if(sum < kLimit)
                    issum[sum] = true;
            }
        }
    }

    // -- finally go through the list of flags and sum all the ones that are still false
    nuint result = 0;
    for(nuint i = 0; i < kLimit; ++i) {
        if(!issum[i])
            result += i;
    }

    CLog::Write("The sum of all numbers that can't be written\n"
                "as a sum of two abundant numbers is " NUintFmt_ "\n", result);

    Assert_(result == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
