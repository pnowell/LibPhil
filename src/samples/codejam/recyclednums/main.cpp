// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"
#include <stdio.h>

// ------------------------------------------------------------------------------------------------
// Convert the given number to a table of decimal digits
// ------------------------------------------------------------------------------------------------
uintn TopDigit(uintn val) {
    if(val == 0)
        return 0;
    val /= 10;
    uintn result = 1;
    while(val > 0) {
        result *= 10;
        val /= 10;
    }
    return result;
}

// ------------------------------------------------------------------------------------------------
// The actual analysis
// ------------------------------------------------------------------------------------------------
uintn NumRecycledPairs(uintn a, uintn b) {
    uintn topdigit = TopDigit(a);
    uintn result = 0;

    // -- start from a and march upward
    for(uintn i = a; i < b; ++i) {
        uintn rot = i;
        // -- rotate through all the variations of this number, ignoring anything less
        // -- than the starting number
        do {
            // -- if we cycle some leading zeros, keep rotating until there's a non-zero digit
            // -- at the top
            do {
                rot = (rot / 10) + (rot % 10) * topdigit;
            } while(rot < topdigit);

            // -- add it as another recycled pair
            if(rot > i && rot <= b)
                ++result;
        } while(rot != i);
    }

    return result;
}

// ================================================================================================
// Main
// ================================================================================================
int main(int32 argc, int8* argv[]) {
    // -- make sure we're given a file name
    if(argc < 2) {
        CLog::Write("You need to give me a filename, please\n");
        return 0;
    }

    // -- try to open it
    FILE* fp = NULL;
    fopen_s(&fp, argv[1], "r");

    // -- make sure we could open it
    if(fp == NULL) {
        CLog::Write("Don't know that file\n");
        return 0;
    }

    // -- read stuff
    uint32 numtests;
    fscanf_s(fp, "%d", &numtests);

    for(uintn i = 0; i < numtests; ++i) {
        // -- read in the two numbers
        uint32 a, b;
        fscanf_s(fp, "%d", &a);
        fscanf_s(fp, "%d", &b);

        uintn result = NumRecycledPairs(a, b);

        // -- write the result
        CLog::Write("Case #%d: %lld\n", i + 1, result);
    }

    // -- close the file
    fclose(fp);

    return 0;
}
