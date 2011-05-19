// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"

// -- constants
static const nuint kNumPermutation = 1000000;
static const nuint kAnswer = 2783915460;

// ------------------------------------------------------------------------------------------------
// Get the nth permutation of n digits
// ------------------------------------------------------------------------------------------------
static nuint Permutation(nuint n) {
    // -- make a sorted table of the available digits while calculating 10!
    CTable<nuint> digits;
    nuint limit = 1;
    for(nuint i = 0; i < 10; ++i) {
        digits.Grow(i);
        limit *= i + 1;
    }

    // -- expect an input from 1 to the number of permutations
    Assert_(0 < n && n <= limit, "Permutation index " NUintFmt_ " is out of bounds", n);
    // -- offset the input to be from 0 to less than the number of permutations
    --n;

    // -- we start by putting a digit that's as small as possible into the highest digits
    nuint mult = 1000000000;
    nuint result = 0;

    // -- for each digit that we need to generate
    for(nuint i = 10; i > 0; --i) {
        // -- reduce our limit to count the number of possible permutations of the digits past
        // -- the current one
        limit /= i;

        // -- pick which remaining digit to add in next, this is done by seeing how many full
        // -- sets of permutations of the remaining digits we'd need to go through before reaching
        // -- the desired index
        nuint which = n / limit;
        result += mult * digits[which];

        // -- remove the digit to make sure we don't use it again
        digits.Remove(which);

        // -- reduce the remaining index to be an index into the permutations of the
        // -- remaining digits
        n -= limit * which;

        // -- reduce the multiplier to use for the next round
        mult /= 10;
    }

    return result;
}

// ================================================================================================
// Problem 24
// ================================================================================================
int32 Problem24() {
    nuint perm = Permutation(kNumPermutation);
    printf("The " NUintFmt_ " permutation is " NUintFmt_ "\n", kNumPermutation, perm);

    Assert_(perm == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}

