#pragma once

#include "core/types.h"

// ================================================================================================
// Static functionality for managing memory
// ================================================================================================
class CMemory {

public:

    static vpointer Alloc(nuint size);
    static vpointer ReAlloc(vpointer m, nuint size);
    static void Free(vpointer m);
};

