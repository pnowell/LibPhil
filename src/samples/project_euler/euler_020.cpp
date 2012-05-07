// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cbigint.h"
#include "io/clog.h"

// -- constants
static const uintn kFactorial = 100;
static const uintn kAnswer = 648;

// ================================================================================================
// Problem 20
// ================================================================================================
int32 Problem20() {
    CBigInt product(1);
    for(uintn i = 1; i <= kFactorial; ++i)
        product *= i;

    uintn numdigits = product.NumDigits();
    uintn sum = 0;
    for(uintn i = 0; i < numdigits; ++i)
        sum += product.Digit(i);

    CLog::Write("The sum of the digits of " NUintFmt_ "! are " NUintFmt_ "\n", kFactorial, sum);

    Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
