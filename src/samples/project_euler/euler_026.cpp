// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"
#include "io/clog.h"

// -- constants
static const uintn kMax = 1000;
static const uintn kAnswer = 983;

// ------------------------------------------------------------------------------------------------
// Get the length of the recurring cycle (zero if it doesn't repeat at all)
// ------------------------------------------------------------------------------------------------
static uintn CycleLength(uintn denom) {
    uintn curr = 1;

    CTable<uintn> remain;
    while(curr != 0) {
        curr *= 10;
        uintn div = curr / denom;
        curr -= denom * div;
        remain.Grow(curr);

        // -- look through the previous remainders to see if we've started repeating
        for(uintn i = remain.Count() - 1; i > 0;) {
            --i;
            if(remain[i] == curr)
                return remain.Count() - 1 - i;
        }
    }

    // -- if we exited the loop, we finished the decimal expansion, so there's no cycle
    return 0;
}

// ================================================================================================
// Problem 26
// ================================================================================================
int32 Problem26() {
    uintn longest = 0;
    uintn longestlen = 0;

    for(uintn i = 2; i < kMax; ++i) {
        uintn len = CycleLength(i);
        if(len > longestlen) {
            longest = i;
            longestlen = len;
        }
    }

    CLog::Write("The number with the longest cycle length of " UintNFmt_ " is " UintNFmt_ "\n",
                longestlen, longest);

    Assert_(longest == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}

