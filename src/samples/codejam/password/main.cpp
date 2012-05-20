// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"
#include <stdio.h>

// -- globals
uint32 typed = 0;
uint32 len = 0;
CTable<real64> prob;

// ================================================================================================
// ================================================================================================
real64 GetBest(real64 probsofar, uintn pos, real64 bestsofar) {
    real64 best = bestsofar;
    while(pos <= typed) {
        // -- first consider if we erased all the characters to this position and typed it out
        uintn bs = typed - pos;
        uintn keysright = bs + len - pos + 1;
        uintn keyswrong = keysright + len + 1;
        real64 finish = probsofar * real64(keysright);
        finish += (1.0f - probsofar) * real64(keyswrong);

        if(finish < best)
            best = finish;

        if(pos < typed)
            probsofar *= prob[pos];
        ++pos;
    }
    
    return best;
}

// ================================================================================================
// Main
// ================================================================================================
int main(sint32 argc, sint8* argv[]) {
    // -- make sure we're given a file name
    if(argc < 2) {
        Log_("You need to give me a filename, please\n");
        return 0;
    }

    // -- try to open it
    FILE* fp = NULL;
    fopen_s(&fp, argv[1], "r");

    // -- make sure we could open it
    if(fp == NULL) {
        Log_("Don't know that file\n");
        return 0;
    }

    // -- read stuff
    uint32 numtests;
    fscanf_s(fp, "%d", &numtests);

    for(uintn i = 0; i < numtests; ++i) {
        fscanf_s(fp, "%d %d", &typed, &len);
        prob.Clear();
        prob.GrowMultiple(len);
        for(uintn j = 0; j < typed; ++j)
            fscanf_s(fp, "%Lf", &prob[j]);

        // -- what if we just press enter and start over
        real64 restart = real64(1 + len + 1);
        real64 result = GetBest(1.0f, 0, restart);
        if(restart < result)
            result = restart;
        Log_("Case #%d: %.6Lf\n", i+1, result);
        prob.Clear();
    }

    // -- close the file
    fclose(fp);

    return 0;
}
