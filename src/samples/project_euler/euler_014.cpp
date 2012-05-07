// -- libs includes
#include "core/types.h"
#include "containers/ctable.h"
#include "io/clog.h"

// -- consts
static const uintn kMaxResult = 1000000;
static const uintn kAnswer = 837799;

// ================================================================================================
// Problem 14
// ================================================================================================
int32 Problem14() {
    CTable<uintn> lengths;
    lengths.GrowMultiple(0, kMaxResult);

    lengths[0] = 1;

    uintn maxval = 0;

    for(uintn i = 1; i < kMaxResult; ++i) {
        if(lengths[i] != 0)
            continue;

        uintn curr = i + 1;
        uintn len = 0;

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
    uintn longest = 0;
    for(uintn i = 0; i < kMaxResult; ++i) {
        if(lengths[i] > longest)
            longest = lengths[i];
    }

    // -- now show all the results with that length
    CLog::Write("Values got up to " UintNFmt_ "\n", maxval);
    for(uintn i = 0; i < kMaxResult; ++i) {
        if(lengths[i] == longest) {
            CLog::Write(UintNFmt_ " starts a chain of length " UintNFmt_ "\n", i+1, longest);
            Assert_(i+1 == kAnswer, "Answer should have been " UintNFmt_, kAnswer);
        }
    }
    
    return 0;
}
