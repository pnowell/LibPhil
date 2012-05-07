// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"
#include "containers/ctable.h"
#include "numerics/cprimecalculator.h"

// -- local includes
#include "euler.h"

// -- constants
static const uintn kAnswer = 55;

// ================================================================================================
// Problem 35
// ================================================================================================
int32 Problem35() {
    CPrimeCalculator& primecalc = PrimeCalculator();
    CLog::Write("Calculating primes...");
    primecalc.FindPrimesUpTo(1000000);
    CLog::Write("Done\n");

    const uintn place[6] = {
        1, 10, 100, 1000, 10000, 100000
    };

    uintn count = 0;
    uintn maxdigits = 6;

    uintn numprimes = primecalc.NumPrimes();
    for(uintn i = 0; i < numprimes; ++i) {
        uintn curr = primecalc.Prime(i);

        // -- count the number of digits
        uintn digits = 0;
        uintn decomp = curr;
        while(decomp > 0) {
            ++digits;
            decomp /= 10;
        }   

        if(digits > maxdigits)
            break;

        // -- check each rotation to see if it's a prime
        decomp = curr;
        nflag smallest = true;
        do {
            decomp = decomp % 10 * place[digits - 1] + decomp / 10;
            if(decomp < curr) {
                smallest = false;
                break;
            }
        } while(decomp != curr);

        // -- if we're not the smallest, don't bother (since we would have found it earlier
        // -- if curr is part of a circle of primes)
        if(!smallest)
            continue;

        decomp = curr;
        uintn toadd = 0;
        nflag allprime = true;
        do {
            decomp = decomp % 10 * place[digits - 1] + decomp / 10;
            if(!primecalc.IsPrime(decomp)) {
                allprime = false;
                break;
            }
            ++toadd;
        } while(decomp != curr);

        // -- if they were all prime
        if(!allprime)
            continue;

        CLog::Write("Found circular primes:");
        // -- do it again to print things out
        decomp = curr;
        do {
            CLog::Write(" " UintNFmt_, decomp);
            decomp = (decomp % 10) * place[digits - 1] + decomp / 10;
        } while(decomp != curr);
        CLog::Write("\n");

        // -- add it to the count
        count += toadd;
    }

    CLog::Write("There are " UintNFmt_ " circular primes\n", count);

    Assert_(count == kAnswer, "The answer should have been " UintNFmt_, kAnswer);
    
    return 0;
}
