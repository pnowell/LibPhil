// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"

// -- constants
static const uintn kCoin[7] = {
    200,
    100,
    50,
    20,
    10,
    5,
    2,
};
static const uintn kLimit = 200;
static const uintn kAnswer = 73682;

// ================================================================================================
// Problem 31
// ================================================================================================
sint32 Problem31() {
    // -- how many ways can we add up to something less than or equal to 200 using
    // -- the above denominations (we don't count the 1p coin, since it can always be
    // -- used to fill in the rest of whatever we're missing)
    uintn result = 0;
    for(uintn i0 = 0; i0 * kCoin[0] <= kLimit; ++i0) {
        uintn sum0 = i0 * kCoin[0];
        for(uintn i1 = 0; sum0 + i1 * kCoin[1] <= kLimit; ++i1) {
            uintn sum1 = i1 * kCoin[1] + sum0;
            for(uintn i2 = 0; sum1 + i2 * kCoin[2] <= kLimit; ++i2) {
                uintn sum2 = i2 * kCoin[2] + sum1;
                for(uintn i3 = 0; sum2 + i3 * kCoin[3] <= kLimit; ++i3) {
                    uintn sum3 = i3 * kCoin[3] + sum2;
                    for(uintn i4 = 0; sum3 + i4 * kCoin[4] <= kLimit; ++i4) {
                        uintn sum4 = i4 * kCoin[4] + sum3;
                        for(uintn i5 = 0; sum4 + i5 * kCoin[5] <= kLimit; ++i5) {
                            uintn sum5 = i5 * kCoin[5] + sum4;
                            for(uintn i6 = 0; sum5 + i6 * kCoin[6] <= kLimit; ++i6) {
                                uintn sum6 = i6 * kCoin[6] + sum5;
                                for(uintn i7 = 0; sum6 + i7 * kCoin[7] <= kLimit; ++i7) {
                                    ++result;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    CLog::Write("The number of combinations is " UintNFmt_ "\n", result);
    Assert_(result == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}
