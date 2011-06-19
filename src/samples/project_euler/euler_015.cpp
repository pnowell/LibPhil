// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"

// -- consts
static const nuint kGridSize = 21;
static const uint64 kAnswer = 137846528820LL;

// ================================================================================================
// Problem 15
// ================================================================================================
int32 Problem15() {
    uint64 grid[kGridSize][kGridSize];

    // -- initialize the top row
    for(nuint i = 0; i < kGridSize; ++i)
        grid[i][0] = 1;

    // -- process all other rows
    for(nuint j = 1; j < kGridSize; ++j) {
        grid[0][j] = 1;
        for(nuint i = 1; i < kGridSize; ++i)
            grid[i][j] = grid[i-1][j] + grid[i][j-1];
    }

    CLog::Write("Number of paths is %lld\n", grid[kGridSize-1][kGridSize-1]);
    Assert_(grid[kGridSize-1][kGridSize-1] == kAnswer,
            "The answer should have been %lld", kAnswer);

    return 0;
}
