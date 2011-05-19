// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"

// -- constants
static const nuint kSize = 1001;
static const nuint kAnswer = 669171001;

// ================================================================================================
// Problem 28
// ================================================================================================
int32 Problem28() {
    nuint sum = 1;
    nuint last = 1;
    for(nuint level = 1; level*2 + 1 <= kSize; ++level) {
        // -- add in the lower right corner
        sum += last + level * 2;
        // -- add in the lower left corner
        sum += last + level * 4;
        // -- add in the upper left corner
        sum += last + level * 6;
        // -- add in the upper right corner
        sum += last + level * 8;
        // -- set last for the next round
        last += level * 8;
    }

    printf("The sum of the diagonals of the " NUintFmt_ "x" NUintFmt_ " square is " NUintFmt_ "\n",
           kSize, kSize, sum);
    Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);
    
    return 0;
}
