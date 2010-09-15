// -- system includes
#include <stdlib.h>

// -- libs includes
#include "core/cmemory.h"

// -- include the guts of the memory allocator
//#include "core/dlmalloc.c"

// ================================================================================================
// Make a new allocation of the give size
// ================================================================================================
vpointer CMemory::Alloc(nuint size) {
    return malloc(size);
}

// ================================================================================================
// Adjust the given allocation (or make a new one if NULL is passed in) to be the new size
// ================================================================================================
vpointer CMemory::ReAlloc(vpointer mem, nuint size) {
    return realloc(mem, size);
}

// ================================================================================================
// Free the given memory
// ================================================================================================
void CMemory::Free(vpointer mem) {
    free(mem);
}

