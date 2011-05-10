// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "containers/ctable.h"

// -- consts
static const nuint kMaxResult = 1000000;
static const nuint kMaxConsidered = 100000000;
static const nuint kAnswer = 910107;

// ------------------------------------------------------------------------------------------------
// Explore a particular branch
// ------------------------------------------------------------------------------------------------
static void FollowChain(nuint val, nuint len, nuint& bestval, nuint& bestlen) {
    while(val < kMaxConsidered) {
        // -- check to see if this qualifies as a new record
        if(val < kMaxResult && bestlen < len) {
            bestlen = len;
            bestval = val;
        }

        // -- add one to the current length
        ++len;

        // -- check to see if we can decrease
        nuint decrease = (val-1) / 3;
        // -- we can only decrease if val-1 is divisible by 3, and if the resulting value is odd
        if((val-1) % 3 == 0 && (decrease & 1) == 1)
            FollowChain(decrease, len, bestval, bestlen);

        val = 2*val;
    }
}

// ================================================================================================
// Problem 14
// ================================================================================================
int32 Problem14() {
    // -- we start off at 8 (in the sequence 1, 2, 4, 8, ...)
    nuint bestval = 1;
    nuint bestlen = 1;
    nuint val = 8;
    nuint len = 4;

    FollowChain(val, len, bestval, bestlen);

    // -- print our results
    printf("The longest chain starts at " NUintFmt_ " and has a length of " NUintFmt_ "\n",
           bestval, bestlen);

    Assert_(bestval == kAnswer, "The answer should have been " NUintFmt_, kAnswer);
    
    return 0;
}
