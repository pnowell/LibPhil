// -- libs includes
#include "core/types.h"
#include "numerics/cbigint.h"
#include "io/clog.h"

// -- consts
static const uintn kMax = 1000;
static const uintn kAnswer = 1366;

// ================================================================================================
// Problem 16
// ================================================================================================
sint32 Problem16() {
    CBigInt power(1);
    for(uintn i = 0; i < kMax; ++i)
        power *= 2;

    // -- print the number
    CLog::Write("2^" UintNFmt_ " = ", kMax);
    uintn numdigits = power.NumDigits();
    for(uintn i = numdigits; i > 0;) {
        --i;
        CLog::Write(UintNFmt_, power.Digit(i));
    }
    CLog::Write("\n");

    // -- calculate the sum
    uintn sum = 0;
    for(uintn i = 0; i < numdigits; ++i)
        sum += power.Digit(i);
    CLog::Write("Sum of digits = " UintNFmt_ "\n", sum);

    Assert_(sum == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}
