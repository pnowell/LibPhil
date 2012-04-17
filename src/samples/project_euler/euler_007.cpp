// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "core/assert.h"
#include "numerics/cprimecalculator.h"
#include "io/clog.h"

// -- local includes
#include "euler.h"

// -- consts
static const nuint kWhichPrime = 10001;
static const nuint kAnswer = 104743;

// ================================================================================================
// Find the 10001st prime number
// ================================================================================================
int32 Problem7() {
    CPrimeCalculator& primecalc = PrimeCalculator();
    while(primecalc.NumPrimes() < kWhichPrime)
        primecalc.CheckNext();

    nuint answer = primecalc.Prime(kWhichPrime-1);
    CLog::Write("The " NUintFmt_ " prime is " NUintFmt_ "\n", kWhichPrime, answer);

    Assert_(answer == kAnswer, "Incorrect answer");

    return 0;
}

