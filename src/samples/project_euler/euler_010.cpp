// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"
#include "io/clog.h"

// -- local includes
#include "euler.h"

// -- consts
static const uintn kMaxPrime = 2000000;
static const uint64 kAnswer = 142913828922LL;

// ================================================================================================
// Find the sum of all primes less than 2 million
// ================================================================================================
sint32 Problem10() {
    uintn i;

    // -- set up the prime calculator and calculate all the primes up to the limit
    CPrimeCalculator& primecalc = PrimeCalculator();
    primecalc.FindPrimesUpTo(kMaxPrime);
    uintn numprimes = primecalc.NumPrimes();
    uint64 sum = 0;
    for(i = 0; i < numprimes; ++i) {
        uintn currprime = primecalc.Prime(i);
        if(currprime >= kMaxPrime)
            break;
        sum += currprime;
    }

    CLog::Write("The sum of all primes less than " UintNFmt_ " is %lld\n", kMaxPrime, sum);
    Assert_(sum == kAnswer, "Looks like I got the wrong answer");

    return 0;
}
