// -- libs includes
#include "core/types.h"
#include "numerics/cbigint.h"
#include "io/clog.h"

// -- consts
static const nuint kMax = 1000;
static const nuint kAnswer = 1366;

// ================================================================================================
// Problem 16
// ================================================================================================
int32 Problem16() {
    CBigInt power(1);
    for(nuint i = 0; i < kMax; ++i)
        power *= 2;

    // -- print the number
    CLog::Write("2^" NUintFmt_ " = ", kMax);
    nuint numdigits = power.NumDigits();
    for(nuint i = numdigits; i > 0;) {
        --i;
        CLog::Write(NUintFmt_, power.Digit(i));
    }
    CLog::Write("\n");

    // -- calculate the sum
    nuint sum = 0;
    for(nuint i = 0; i < numdigits; ++i)
        sum += power.Digit(i);
    CLog::Write("Sum of digits = " NUintFmt_ "\n", sum);

    Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
