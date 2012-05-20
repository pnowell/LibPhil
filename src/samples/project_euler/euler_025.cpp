// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cbigint.h"
#include "io/clog.h"

// -- constants
static const uintn kNumDigits = 1000;
static const uintn kAnswer = 4782;

// ================================================================================================
// Problem 25
// ================================================================================================
sint32 Problem25() {
    CBigInt f0(1);
    CBigInt f1(1);
    uintn i0 = 1;
    uintn i1 = 2;

    while(f0.NumDigits() < kNumDigits && f1.NumDigits() < kNumDigits) {
        f0 += f1;
        f1 += f0;
        i0 += 2;
        i1 += 2;
    }

    uintn result = f0.NumDigits() >= kNumDigits ? i0 : i1;
    CLog::Write("The first fibonacci number to have at least " UintNFmt_ " digits is f"
                UintNFmt_ "\n", kNumDigits, result);

    Assert_(result == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}
