// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"
#include "numerics/cprimecalculator.h"
#include "io/clog.h"

// -- local includes
#include "euler.h"

// -- constants
static const uintn kMax = 1000;
static const intn kAnswer = -59231;

// ================================================================================================
// Problem 27
// ================================================================================================
int32 Problem27() {
    // -- find more primes than we'll need
    CLog::Write("Calculating primes ... ");
    CPrimeCalculator& calc = PrimeCalculator();
    calc.FindPrimesUpTo(2*kMax*kMax + kMax);
    CLog::Write("Done\n");

    CLog::Write("Making table of is-prime flags ... ");
    // -- make a table of flags to say if each number is prime
    CTable<uint64> isprime;
    uintn numprimes = calc.NumPrimes();
    for(uintn i = 0; i < numprimes; ++i) {
        uintn prime = calc.Prime(i);
        uintn idx = prime / 64;
        uintn bit = prime - idx * 64;

        // -- make sure we have enough in the isprime table
        if(idx >= isprime.Count())
            isprime.GrowMultiple(0, idx + 1 - isprime.Count());

        // -- set the appropriate bit
        isprime[idx] |= uint64(1) << bit;
    }
    CLog::Write("Done\n");

    intn besta = 0;
    intn bestb = 0;
    uintn bestlen = 0;

    // -- b has to be a prime since n has to be able to start at zero
    uintn pidx = 0;
    for(; calc.Prime(pidx) < 1000; ++pidx) {
        // -- take b as the current prime
        intn b = intn(calc.Prime(pidx));

        // -- we need to calculate a so that 1 + a + b is prime
        // -- so we look through for a in the range b - 999 < a < b + 1000
        intn mina = -1000;
        intn maxa = 1000;

        // -- we just want to make sure n=1 still yields a positive number
        if(1 + mina + b < 1)
            mina = -b;

        // -- look for the first a to fall in the range (so that 1 + a + b is a prime)
        uintn apidx = 0;
        while(intn(calc.Prime(apidx)) - b - 1 < mina)
            ++apidx;

        // -- now for every candidate for a that is within the range, check to see
        // -- how many primes we get
        for(; intn(calc.Prime(apidx)) < maxa; ++apidx) {
            intn a = calc.Prime(apidx) - b - 1;

            uintn len = 0;
            uintn idx = 0;
            uintn bit = 0;
            do {
                ++len;

                // -- recalculate bit and idx
                intn candidate = len*len + a*len + b;
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
        CLog::Write("The best quadratic is n^2 - " NIntFmt_ "*n + " NUintFmt_ "\n", -besta, bestb);
    else
        CLog::Write("The best quadratic is n^2 + " NIntFmt_ "*n + " NUintFmt_ "\n", besta, bestb);
    CLog::Write("It yields primes in the range n=0 to " NUintFmt_ "\n", bestlen-1);
    CLog::Write("So the product a*b=" NIntFmt_ "\n", besta*bestb);

    Assert_(besta * bestb == kAnswer, "The answer should have been " NIntFmt_, kAnswer);

    return 0;
}

