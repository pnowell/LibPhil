#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// Class for all logging we need to do
// ================================================================================================
class CLog {

public:

    // -- stand in for printf
    static void Write(cpointer fmt, ...);
};

#define Log_(fmt, ...) CLog::Write(fmt, ##__VA_ARGS__)
