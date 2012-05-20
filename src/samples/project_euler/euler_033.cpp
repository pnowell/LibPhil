// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"
#include "numerics/cfactorizer.h"
#include "numerics/cprimecalculator.h"

// -- local includes
#include "euler.h"

// -- constants
static const uintn kAnswer = 100;

// ------------------------------------------------------------------------------------------------
// Structure to hold a fractional value
// ------------------------------------------------------------------------------------------------
struct SFrac {
    uintn num;
    uintn den;

    // -- constructor
    SFrac(uintn n, uintn d) : num(n), den(d) {}
};

// ================================================================================================
// Problem 33
// ================================================================================================
sint32 Problem33() {
    CTable<SFrac> fractions;

    uintn id[2];
    uintn jd[2];
    for(uintn i = 11; i <= 99; ++i) {
        id[0] = i % 10;
        id[1] = i / 10;

        // -- skip all multiples of 10 (since we can't cancel the zeros)
        if(id[0] == 0)
            continue;

        for(uintn j = i+1; j <= 99; ++j) {
            jd[0] = j % 10;
            jd[1] = j / 10;

            // -- skip multiples of 10
            if(jd[0] == 0)
                continue;

            // -- check for common digits to cancel
            // -- i/j == id[m] / jd[n] 
            for(uintn m = 0; m < 2; ++m) {
                for(uintn n = 0; n < 2; ++n) {
                    if(id[m] == jd[n]) {
                        if(j * id[1-m] == i * jd[1-n]) {
                            fractions.Grow(SFrac(i, j));
                            CLog::Write("Found fraction " UintNFmt_ " / " UintNFmt_ "\n", i, j);
                        }
                    }
                }
            }
        }
    }

    // -- now multiply all the fractions together, building a list of all the prime factors
    // -- as we go along
    CTable<uintn> numfactors;
    CTable<uintn> denfactors;
    CPrimeCalculator& primecalc = PrimeCalculator();
    uintn count = fractions.Count();
    SFrac result(1, 1);
    for(uintn i = 0; i < count; ++i) {
        SFrac& curr = fractions[i];
        result.num *= curr.num;
        result.den *= curr.den;
        CFactorizer::CollectFactors(curr.num, primecalc, numfactors, false);
        CFactorizer::CollectFactors(curr.den, primecalc, denfactors, false);
    }

    CLog::Write("The product of all those is " UintNFmt_ " / " UintNFmt_ "\n",
                result.num, result.den);

    // -- sort the list of factors for the numerator and denominator
    numfactors.Sort<CompareBasicTypes<uintn> >();
    denfactors.Sort<CompareBasicTypes<uintn> >();

    // -- iterate through the factors together removing common factors
    uintn i = 0;
    uintn j = 0;
    uintn numcount = numfactors.Count();
    uintn dencount = denfactors.Count();
    while(i < numcount && j < dencount) {
        uintn nf = numfactors[i];
        uintn df = denfactors[j];
        if(nf == df) {
            result.num /= nf;
            result.den /= df;
            ++i;
            ++j;

            CLog::Write("Removing common factor " UintNFmt_ " -> " UintNFmt_ " / " UintNFmt_ "\n",
                        nf, result.num, result.den);
        }
        else if(nf < df)
            ++i;
        else
            ++j;
    }

    CLog::Write("The denominator is " UintNFmt_ "\n", result.den);

    Assert_(result.den == kAnswer, "The answer should have been " UintNFmt_, kAnswer);
    
    return 0;
}
