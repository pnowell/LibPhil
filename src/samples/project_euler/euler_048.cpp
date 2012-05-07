// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "numerics/cbigint.h"
#include "io/clog.h"

// -- constants
static const uintn kLastNumber = 1000;
static const uintn kNumDigits = 10;
static cpointer kAnswer = "9110846700";

// ================================================================================================
// Problem 48
// ================================================================================================
int32 Problem48() {
    CBigInt result;
    result.SetDigitLimit(kNumDigits);

    CBigInt temp;
    temp.SetDigitLimit(kNumDigits);

    for(uintn i = 1; i <= kLastNumber; ++i) {
        // -- we don't need to bother with multiples of 10, since
        // -- they'll all end up with at least ten zeros in their least significant digits
        if((i % 10) == 0)
            continue;

        // -- initialize temp to 1
        temp = 1;
        for(uintn j = 0; j < i; ++j) {
            temp *= i;
        }
        result += temp;
    }

    CLog::Write("The last " NUintFmt_ " digits of the sum are \"", kNumDigits);
    nflag correct = true;
    for(uintn i = kNumDigits; i > 0;) {
        --i;
        CLog::Write(NUintFmt_, result.Digit(i));
        if(int8(result.Digit(i) + '0') != kAnswer[kNumDigits-i-1])
            correct = false;
    }
    CLog::Write("\"\n");

    Assert_(correct, "The answer should have been \"%s\"", kAnswer);

    return 0;
}
