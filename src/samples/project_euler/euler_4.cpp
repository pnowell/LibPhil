// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"

// -- consts
static const uint32 kMaxDigits = 8;

// ================================================================================================
// Find the largest palindrome that's a product of a pair of 3 digit numbers
// ================================================================================================
int32 Problem4() {
    uint32 f1 = 999;
    uint32 f2 = 999;
    uint32 product;
    uint32 digits[kMaxDigits];
    uint32 i, j;
    uint32 largest = 0;

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
            if(digits[j] != digits[i]) {
                /*
                printf("%d * %d = %d isn't a palindrome because %d != %d\n",
                       f1, f2, f1*f2, digits[i], digits[j]);
                */
                break;
            }
        }

        if(j >= i) {
            printf("Found the palindrome %d = %d * %d\n", f1 * f2, f1, f2);
            if(f1 * f2 > largest)
                largest = f1 * f2;

            // -- once we've found a palindrome, we don't need to keep decrementing f1
            f2 -= 1;
            f1 = 999;

            printf("f2 * 999 = %d * 999 = %d\n", f2, f2 * f2);
        }
        else {
            f1 -= 1;
            if(f1 < f2) {
                f2 -= 1;
                f1 = 999;
            }
        }
    }

    if(largest == 0)
        printf("Didn't find anything!\n");
    else
        printf("Found the largest is %d\n", largest);

    return 0;
}
