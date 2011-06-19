// -- system includes
#include <stdarg.h>
#include <stdio.h>

// -- libs includes
#include "core/assert.h"
#include "io/clog.h"

#if Debug_

// ================================================================================================
// A globally scoped function for handling the failed assertions
// ================================================================================================
void AssertHandler(cpointer file, nuint line, cpointer errorfmt, ...) {
    CLog::Write("\n+===================+\n");
    CLog::Write("| Assertion failure |\n");
    CLog::Write("+===================+\n");
    CLog::Write("| File  : %s\n| Line  : " NUintFmt_ "\n| Error : ", file, line);

    // -- print the error
    va_list args;
    va_start(args, errorfmt);
    vprintf(errorfmt, args);
    va_end(args);
    CLog::Write("\n");
}

#endif // Debug_

