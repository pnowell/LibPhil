// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"
#include "numerics/cprimecalculator.h"

// -- constants
static const nuint kMax = 1000;
static const nint kAnswer = -59231;

// ================================================================================================
// Problem 27
// ================================================================================================
int32 Problem27() {
    // -- find more primes than we'll need
    printf("Calculating primes ... ");
    CPrimeCalculator calc;
    calc.FindPrimesUpTo(2*kMax*kMax + kMax);
    printf("Done\n");

    printf("Making table of is-prime flags ... ");
    // -- make a table of flags to say if each number is prime
    CTable<uint64> isprime;
    nuint numprimes = calc.NumPrimes();
    for(nuint i = 0; i < numprimes; ++i) {
        nuint prime = calc.Prime(i);
        nuint idx = prime / 64;
        nuint bit = prime - idx * 64;

        // -- make sure we have enough in the isprime table
        if(idx >= isprime.Count())
            isprime.GrowMultiple(0, idx + 1 - isprime.Count());

        // -- set the appropriate bit
        isprime[idx] |= uint64(1) << bit;
    }
    printf("Done\n");

    nint besta = 0;
    nint bestb = 0;
    nuint bestlen = 0;

    // -- b has to be a prime since n has to be able to start at zero
    nuint pidx = 0;
    for(; calc.Prime(pidx) < 1000; ++pidx) {
        // -- take b as the current prime
        nint b = nint(calc.Prime(pidx));

        // -- we need to calculate a so that 1 + a + b is prime
        // -- so we look through for a in the range b - 999 < a < b + 1000
        nint mina = -1000;
        nint maxa = 1000;

        // -- we just want to make sure n=1 still yields a positive number
        if(1 + mina + b < 1)
            mina = -b;

        // -- look for the first a to fall in the range (so that 1 + a + b is a prime)
        nuint apidx = 0;
        while(nint(calc.Prime(apidx)) - b - 1 < mina)
            ++apidx;

        // -- now for every candidate for a that is within the range, check to see
        // -- how many primes we get
        for(; nint(calc.Prime(apidx)) < maxa; ++apidx) {
            nint a = calc.Prime(apidx) - b - 1;

            nuint len = 0;
            nuint idx = 0;
            nuint bit = 0;
            do {
                ++len;

                // -- recalculate bit and idx
                nint candidate = len*len + a*len + b;
                if(candidate < 0)
                    break;
                idx = candidate / 64;
                bit = candidate - idx * 64;
            } while((isprime[idx] & (uint64(1) << bit)) != 0);

            // -- record the new length if it's long enough
            if(len > bestlen) {
                besta = a;
                bestb = b;
                bestlen = len;
            }
        }
    }

    if(besta < 0)
        printf("The best quadratic is n^2 - " NIntFmt_ "*n + " NUintFmt_ "\n", -besta, bestb);
    else
        printf("The best quadratic is n^2 + " NIntFmt_ "*n + " NUintFmt_ "\n", besta, bestb);
    printf("It yields primes in the range n=0 to " NUintFmt_ "\n", bestlen-1);
    printf("So the product a*b=" NIntFmt_ "\n", besta*bestb);

    Assert_(besta * bestb == kAnswer, "The answer should have been " NIntFmt_, kAnswer);

    return 0;
}

