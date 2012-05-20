// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"
#include "numerics/cprimecalculator.h"
#include "numerics/cfactorizer.h"
#include "io/clog.h"

// -- local includes
#include "euler.h"

// -- constants
static const uintn kMaxBase = 100;
static const uintn kMaxPower = 100;
static const uintn kAnswer = 9183;

// ================================================================================================
// Problem 29
// ================================================================================================
sint32 Problem29() {
    // -- first we need all the primes up to 100
    CPrimeCalculator& calc = PrimeCalculator();
    calc.FindPrimesUpTo(kMaxBase);

    CTable<uintn> factor;
    CTable<uintn> factpow;
    CTable<uintn> commondiv;
    CTable<uintn> divisor;

    uintn unique = 0;

    // -- for each base
    for(uintn base = 2; base <= kMaxBase; ++base) {
        // -- get the prime factorization
        CFactorizer::CollectFactors(base, calc, factor);

        // -- if the number itself is its only factor, it's prime and so all the powers
        // -- will be unique
        if(factor[0] == base) {
            unique += 99;
            continue;
        }

        // -- get the powers of each prime factor
        uintn currfact = factor[0];
        factpow.Clear();
        factpow.Grow(1);
        uintn numfact = factor.Count();
        for(uintn i = 1; i < numfact; ++i) {
            if(factor[i] == currfact)
                factpow[factpow.Count() - 1] += 1;
            else {
                factpow.Grow(1);
                currfact = factor[i];
            }
        }
        uintn factcount = factpow.Count();

        // -- loop through all the powers and see if we can reduce the power down to something
        // -- that would have already occurred
        for(uintn power = 2; power <= kMaxPower; ++power) {
            // -- for this power we want to know if we can distribute the power to the powers
            // -- of all the prime factors, and rewrite it with a larger overall power (which
            // -- will have reduced the base to a smaller value) and yet still have the power be
            // -- less than or equal 100
            CFactorizer::CollectFactors(factpow[0] * power, calc, factor);
            CFactorizer::CollectDivisors(factor, commondiv);
            uintn i;
            for(i = 1; i < factcount; ++i) {
                CFactorizer::CollectFactors(factpow[i] * power, calc, factor);
                CFactorizer::CollectDivisors(factor, divisor);
                uintn numdivs = divisor.Count();
                uintn currdiv = 0;
                for(uintn j = 0; j < commondiv.Count();) {
                    while(currdiv < numdivs && divisor[currdiv] < commondiv[j])
                        currdiv++;
                    if(currdiv == numdivs || divisor[currdiv] != commondiv[j])
                        commondiv.Remove(j);
                    else
                        ++j;
                }
            }

            // -- now that we have all the common divisors in commondiv, just walk through them
            // -- to find a divisor bigger than power but less than or equal to 100
            uintn numcommon = commondiv.Count();
            for(i = 0; i < numcommon; ++i) {
                if(commondiv[i] > power && commondiv[i] <= kMaxPower)
                    break;
            }
            if(i == numcommon)
                ++unique;
        }
    }

    CLog::Write("The number of unique numbers is " UintNFmt_ "\n", unique);
    Assert_(unique == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}

