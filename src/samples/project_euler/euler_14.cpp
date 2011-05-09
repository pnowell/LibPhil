// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "containers/ctable.h"

// -- consts
static const nuint kMax = 1000000;

// ------------------------------------------------------------------------------------------------
// Recursive function to walk until we find an existing calculated chain length
// ------------------------------------------------------------------------------------------------
void CalcChainLength(nuint i, CTable<nuint>& chains) {
    // -- first make sure we have that much memory allocated
    if(i >= chains.Count())
        chains.GrowMultiple(0, i + 1 - chains.Count());

    // -- if we already have a value, return
    if(chains[i] != 0)
        return;

    // -- figure out the next number in the chain
    nuint next = (i & 1) ? 3*i + 1 : i >> 1;
    CalcChainLength(next, chains);

    chains[i] = chains[next] + 1;
}

// ================================================================================================
// Problem 14
// ================================================================================================
int32 Problem14() {
    CTable<nuint> chains;
    // -- we know we're going to need at least kMax entries
    chains.GrowMultiple(0, kMax);
    chains[1] = 1;

    for(nuint i = 2; i < kMax; ++i)
        CalcChainLength(i, chains);

    nuint maxlen = 0;
    nuint maxnum = 0;
    for(nuint i = 1; i < kMax; ++i) {
        if(chains[i] > maxlen) {
            maxlen = chains[i];
            maxnum = i;
        }
    }

    printf("The longest chain of length " NUintFmt_ " is " NUintFmt_ "\n", maxlen, maxnum);

    return 0;
}
