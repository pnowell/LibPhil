#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// Static functionality for managing memory
// ================================================================================================
class CMemory {

public:

    // -- allocation
    static vpointer Alloc(nuint size);
    static vpointer ReAlloc(vpointer m, nuint size);
    static vpointer CAlloc(nuint size);

    // -- free
    static void Free(vpointer m);

    // -- move
    static void Move(vpointer from, vpointer to, nuint size);

    // -- destruction
    template<typename T> static void Destroy(T* t);
};

// ================================================================================================
// Templated destruction function
// ================================================================================================
template<typename T> inline void CMemory::Destroy(T* t) {
    t->~T();
}
