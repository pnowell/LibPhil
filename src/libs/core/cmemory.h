#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// Static functionality for managing memory
// ================================================================================================
class CMemory {

public:

    // -- allocation
    static vpointer Alloc(uintn size);
    static vpointer ReAlloc(vpointer m, uintn size);
    static vpointer CAlloc(uintn size);

    // -- free
    static void Free(vpointer m);

    // -- move
    static void Move(vpointer from, vpointer to, uintn size);

    // -- destruction
    template<typename T> static void Destroy(T* t);
};

// ================================================================================================
// Templated destruction function
// ================================================================================================
template<typename T> inline void CMemory::Destroy(T* t) {
    t->~T();
}
