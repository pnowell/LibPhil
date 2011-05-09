// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"

// -- consts
static const nuint kMaxDigits = 8;
static const nuint kAnswer = 906609;

// ================================================================================================
// Find the largest palindrome that's a product of a pair of 3 digit numbers
// ================================================================================================
int32 Problem4() {
    nuint f1 = 999;
    nuint f2 = 999;
    nuint product;
    nuint digits[kMaxDigits];
    nuint i, j;
    nuint largest = 0;

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
            printf("Found the palindrome " NUintFmt_ " = " NUintFmt_ " * " NUintFmt_ "\n",
                   f1 * f2, f1, f2);
            if(f1 * f2 > largest)
                largest = f1 * f2;

            // -- once we've found a palindrome, we don't need to keep decrementing f1
            f2 -= 1;
            f1 = 999;

            printf("f2 * 999 = " NUintFmt_ " * 999 = " NUintFmt_ "\n", f2, f2 * f2);
        }
        else {
            f1 -= 1;
            if(f1 < f2) {
                f2 -= 1;
                f1 = 999;
            }
        }
    }

    printf("Found the largest is " NUintFmt_ "\n", largest);

    Assert_(largest == kAnswer, "Incorrect answer");

    return 0;
}
