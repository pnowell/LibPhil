// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cbigint.h"

// -- constants
static const nuint kFactorial = 100;
static const nuint kAnswer = 648;

// ================================================================================================
// Problem 20
// ================================================================================================
int32 Problem20() {
    CBigInt product(1);
    for(nuint i = 1; i <= kFactorial; ++i)
        product *= i;

    nuint numdigits = product.NumDigits();
    nuint sum = 0;
    for(nuint i = 0; i < numdigits; ++i)
        sum += product.Digit(i);

    printf("The sum of the digits of " NUintFmt_ "! are " NUintFmt_ "\n", kFactorial, sum);

    Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
