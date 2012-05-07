// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"

// -- consts
static const uintn kMaxDigits = 8;
static const uintn kAnswer = 906609;

// ================================================================================================
// Find the largest palindrome that's a product of a pair of 3 digit numbers
// ================================================================================================
int32 Problem4() {
    uintn f1 = 999;
    uintn f2 = 999;
    uintn product;
    uintn digits[kMaxDigits];
    uintn i, j;
    uintn largest = 0;

    while(f2 > 0 && f2 * 999 > largest) {
        product = f1 * f2;

        for(i = 0; i < kMaxDigits; ++i) {
            digits[i] = product % 10;
            product = product / 10;
            if(product == 0)
                break;
        }

        // -- there's one more digit than i
        for(j = 0; j < i; ++j, --i) {
            if(digits[j] != digits[i])
                break;
        }

        if(j >= i) {
            CLog::Write("Found the palindrome " UintNFmt_ " = " UintNFmt_ " * " UintNFmt_ "\n",
                        f1 * f2, f1, f2);
            if(f1 * f2 > largest)
                largest = f1 * f2;

            // -- once we've found a palindrome, we don't need to keep decrementing f1
            f2 -= 1;
            f1 = 999;

            CLog::Write("f2 * 999 = " UintNFmt_ " * 999 = " UintNFmt_ "\n", f2, f2 * f2);
        }
        else {
            f1 -= 1;
            if(f1 < f2) {
                f2 -= 1;
                f1 = 999;
            }
        }
    }

    CLog::Write("Found the largest is " UintNFmt_ "\n", largest);

    Assert_(largest == kAnswer, "Incorrect answer");

    return 0;
}
