// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "core/ctimer.h"
#include "io/clog.h"

// -- constants
static const uintn kAnswer = 0;

// ================================================================================================
// Problem 36
// ================================================================================================
sint32 Problem36() {
    uintn sum = 0;
    CLog::Write("The sum is " UintNFmt_ "\n", sum);
    //Assert_(sum == kAnswer, "The answer should have been " UintNFmt_, kAnswer);
    
    return 0;
}
