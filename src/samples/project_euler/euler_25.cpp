// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cbigint.h"

// -- constants
static const nuint kNumDigits = 1000;
static const nuint kAnswer = 4782;

// ================================================================================================
// Problem 25
// ================================================================================================
int32 Problem25() {
    CBigInt f0(1);
    CBigInt f1(1);
    nuint i0 = 1;
    nuint i1 = 2;

    while(f0.NumDigits() < kNumDigits && f1.NumDigits() < kNumDigits) {
        f0 += f1;
        f1 += f0;
        i0 += 2;
        i1 += 2;
    }

    nuint result = f0.NumDigits() >= kNumDigits ? i0 : i1;
    printf("The first fibonacci number to have at least " NUintFmt_ " digits is f" NUintFmt_,
           kNumDigits, result);

    Assert_(result == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
