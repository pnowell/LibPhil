// -- system includes
#include <stdio.h>
#include <stdarg.h>

// -- libs includes
#include "core/assert.h"

#if Debug_

// ================================================================================================
// A globally scoped function for handling the failed assertions
// ================================================================================================
void AssertHandler(cpointer file, nuint line, cpointer errorfmt, ...) {
    printf("\n+===================+\n");
    printf("| Assertion failure |\n");
    printf("+===================+\n");
    printf("| File  : %s\n| Line  : %d\n| Error : ", file, line);

    // -- print the error
    va_list args;
    va_start(args, errorfmt);
    vprintf(errorfmt, args);
    va_end(args);
    printf("\n");
}

#endif // Debug_

