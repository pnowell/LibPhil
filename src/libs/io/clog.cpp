// -- system includes
#include <stdio.h>
#include <stdarg.h>

// -- libs includes
#include "io/clog.h"

// ================================================================================================
// Stand in for printf
// ================================================================================================
void CLog::Write(cpointer fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
