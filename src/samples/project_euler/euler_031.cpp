// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"

// -- constants
static const nuint kCoin[7] = {
    200,
    100,
    50,
    20,
    10,
    5,
    2,
};
static const nuint kLimit = 200;
static const nuint kAnswer = 73682;

// ================================================================================================
// Problem 31
// ================================================================================================
int32 Problem31() {
    // -- how many ways can we add up to something less than or equal to 200 using
    // -- the above denominations (we don't count the 1p coin, since it can always be
    // -- used to fill in the rest of whatever we're missing)
    nuint result = 0;
    for(nuint i0 = 0; i0 * kCoin[0] <= kLimit; ++i0) {
        nuint sum0 = i0 * kCoin[0];
        for(nuint i1 = 0; sum0 + i1 * kCoin[1] <= kLimit; ++i1) {
            nuint sum1 = i1 * kCoin[1] + sum0;
            for(nuint i2 = 0; sum1 + i2 * kCoin[2] <= kLimit; ++i2) {
                nuint sum2 = i2 * kCoin[2] + sum1;
                for(nuint i3 = 0; sum2 + i3 * kCoin[3] <= kLimit; ++i3) {
                    nuint sum3 = i3 * kCoin[3] + sum2;
                    for(nuint i4 = 0; sum3 + i4 * kCoin[4] <= kLimit; ++i4) {
                        nuint sum4 = i4 * kCoin[4] + sum3;
                        for(nuint i5 = 0; sum4 + i5 * kCoin[5] <= kLimit; ++i5) {
                            nuint sum5 = i5 * kCoin[5] + sum4;
                            for(nuint i6 = 0; sum5 + i6 * kCoin[6] <= kLimit; ++i6) {
                                nuint sum6 = i6 * kCoin[6] + sum5;
                                for(nuint i7 = 0; sum6 + i7 * kCoin[7] <= kLimit; ++i7) {
                                    ++result;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("The number of combinations is " NUintFmt_ "\n", result);
    Assert_(result == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
