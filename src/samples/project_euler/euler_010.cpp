// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"
#include "io/clog.h"

// -- consts
static const nuint kMaxPrime = 2000000;
static const uint64 kAnswer = 142913828922LL;

// ================================================================================================
// Find the sum of all primes less than 2 million
// ================================================================================================
int32 Problem10() {
    nuint i;

    // -- set up the prime calculator and calculate all the primes up to the limit
    CPrimeCalculator primecalc;
    primecalc.FindPrimesUpTo(kMaxPrime);
    nuint numprimes = primecalc.NumPrimes();
    uint64 sum = 0;
    for(i = 0; i < numprimes; ++i) {
        nuint currprime = primecalc.Prime(i);
        if(currprime >= kMaxPrime)
            break;
        sum += currprime;
    }

    CLog::Write("The sum of all primes less than " NUintFmt_ " is %lld\n", kMaxPrime, sum);
    Assert_(sum == kAnswer, "Looks like I got the wrong answer");

    return 0;
}
