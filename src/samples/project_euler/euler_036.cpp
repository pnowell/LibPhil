// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "core/ctimer.h"
#include "io/clog.h"

// -- constants
static const nuint kAnswer = 0;

// ================================================================================================
// Problem 36
// ================================================================================================
int32 Problem36() {
    nuint sum = 0;
    CLog::Write("The sum is " NUintFmt_ "\n", sum);
    //Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);
    
    return 0;
}
