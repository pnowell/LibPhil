// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "containers/ctable.h"

// -- consts
static const nuint kMaxResult = 1000000;
static const nuint kAnswer = 837799;

// ================================================================================================
// Problem 14
// ================================================================================================
int32 Problem14() {
    CTable<nuint> lengths;
    lengths.GrowMultiple(0, kMaxResult);

    lengths[0] = 1;

    nuint maxval = 0;

    for(nuint i = 1; i < kMaxResult; ++i) {
        if(lengths[i] != 0)
            continue;

        nuint curr = i + 1;
        nuint len = 0;

        // -- first see how long it takes to find something that's recorded
        do {
            if(curr & 1)
                curr = curr * 3 + 1;
            else
                curr = curr >> 1;
            if(curr > maxval)
                maxval = curr;
            ++len;
        } while(curr >= kMaxResult || lengths[curr - 1] == 0);

        len += lengths[curr - 1];

        // -- then do it again filling in the values
        curr = i + 1;
        do {
            // -- write to this spot in the list if it's within the bounds of the table
            if(curr < kMaxResult)
                lengths[curr - 1] = len;

            // -- go on to the next number
            if(curr & 1)
                curr = curr * 3 + 1;
            else
                curr = curr >> 1;
            --len;
        } while(curr >= kMaxResult || lengths[curr - 1] == 0);
    }

    // -- now go through and find the longest length
    nuint longest = 0;
    for(nuint i = 0; i < kMaxResult; ++i) {
        if(lengths[i] > longest)
            longest = lengths[i];
    }

    // -- now show all the results with that length
    printf("Values got up to " NUintFmt_ "\n", maxval);
    for(nuint i = 0; i < kMaxResult; ++i) {
        if(lengths[i] == longest) {
            printf(NUintFmt_ " starts a chain of length " NUintFmt_ "\n", i+1, longest);
            Assert_(i+1 == kAnswer, "Answer should have been " NUintFmt_, kAnswer);
        }
    }
    
    return 0;
}
