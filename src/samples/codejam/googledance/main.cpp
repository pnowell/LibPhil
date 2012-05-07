// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"

// ------------------------------------------------------------------------------------------------
// Struct to describe a single dancer
// ------------------------------------------------------------------------------------------------
struct SDancer {
    uintn total;
    uintn best;
    uintn surprisebest;

    // -- constructor
    SDancer(uintn t) : total(t), best(0), surprisebest(0) {}
};

// ------------------------------------------------------------------------------------------------
// The actual analysis of a single line
// ------------------------------------------------------------------------------------------------
uintn Analyze(CTable<SDancer>& dancers, uintn surprises, uintn besttarget) {
    // -- keep track of how many dancers beat the besttarget
    uintn result = 0;

    // -- we're going to "spend" our surprises on people that need it to get them up
    // -- to the besttarget best score
    uintn surprisesleft = surprises;

    // -- go through and compute the best score with and without being a surprise
    uintn count = dancers.Count();
    for(uintn i = 0; i < count; ++i) {
        SDancer& curr = dancers[i];
        uintn rem = curr.total % 3;
        uintn div = curr.total / 3;
        uintn best = div;
        uintn surprisebest = div;
        if(rem == 0) {
            best = div;
            if(0 < div && div < 10)
                surprisebest = div + 1;    // div - 1, div, div + 1
            else
                surprisebest = div;        // no difference
        }
        else if(rem == 1) {
            best = div + 1;
            // in this case, even with a surprise, our best score is the same
            // normal   : div, div, div + 1
            // surprise : div - 1, div + 1, div + 1
            surprisebest = best;
        }
        else if(rem == 2) {
            best = div + 1;
            if(div <= 8)
                surprisebest = div + 2;     // div, div, div + 2
            else
                surprisebest = best;
        }

        // -- if best is already better than besttarget, increment the result
        if(best >= besttarget)
            ++result;

        // -- if the best is less than besttarget and surprisebest passes, spend another
        else if(surprisesleft > 0 && surprisebest >= besttarget) {
            --surprisesleft;
            ++result;
        }
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

    // -- keep a table of dancers
    CTable<SDancer> dancers;
    for(uintn i = 0; i < numtests; ++i) {
        uint32 numdancers;
        fscanf_s(fp, "%d", &numdancers);

        // -- get the number of surprises
        uint32 surprises;
        fscanf_s(fp, "%d", &surprises);

        // -- get the cut off best score
        uint32 besttarget;
        fscanf_s(fp, "%d", &besttarget);

        // -- read all the dancers
        for(uintn j = 0; j < numdancers; ++j) {
            uint32 total;
            fscanf_s(fp, "%d", &total);
            dancers.Grow(SDancer(total));
        }

        // -- do the analysis
        uintn result = Analyze(dancers, surprises, besttarget);

        // -- write the result
        CLog::Write("Case #%d: %lld\n", i+1, result);

        // -- clear the table
        dancers.Clear();
    }

    // -- close the file
    fclose(fp);

    return 0;
}
