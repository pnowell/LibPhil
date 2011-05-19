// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"

// -- constants
static const nuint kMax = 1000;
static const nuint kAnswer = 983;

// ------------------------------------------------------------------------------------------------
// Get the length of the recurring cycle (zero if it doesn't repeat at all)
// ------------------------------------------------------------------------------------------------
static nuint CycleLength(nuint denom) {
    nuint curr = 1;

    CTable<nuint> remain;
    while(curr != 0) {
        curr *= 10;
        nuint div = curr / denom;
        curr -= denom * div;
        remain.Grow(curr);

        // -- look through the previous remainders to see if we've started repeating
        for(nuint i = remain.Count() - 1; i > 0;) {
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
    nuint longest = 0;
    nuint longestlen = 0;

    for(nuint i = 2; i < kMax; ++i) {
        nuint len = CycleLength(i);
        if(len > longestlen) {
            longest = i;
            longestlen = len;
        }
    }

    printf("The number with the longest cycle length of " NUintFmt_ " is " NUintFmt_ "\n",
           longestlen, longest);

    Assert_(longest == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}

