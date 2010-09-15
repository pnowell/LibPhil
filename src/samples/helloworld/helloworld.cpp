// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/cmemory.h"

// -- useful macro to show the size of a type
#define ShowSize_(TYPE) printf("The size of " #TYPE " is %d\n", sizeof(TYPE))

// ================================================================================================
// Main
// ================================================================================================
nint main(nint argc, int8* argv[]) {
    ShowSize_(nint);
    ShowSize_(nuint);
    ShowSize_(int8);
    ShowSize_(uint8);
    ShowSize_(int16);
    ShowSize_(uint16);
    ShowSize_(int32);
    ShowSize_(uint32);
    ShowSize_(int64);
    ShowSize_(uint64);

    ShowSize_(nflag);

    ShowSize_(nreal);
    ShowSize_(real32);
    ShowSize_(real64);

    // -- try doing some allocations
    #define numallocs 5
    vpointer allocs[numallocs];
    nuint allocsize[numallocs] = {
        128,
        256,
        512,
        48,
        100,
    };
    printf("Making initial allocations\n");
    for(nuint i = 0; i < numallocs; i++)
        allocs[i] = CMemory::Alloc(allocsize[i]);

    // -- now resize those
    printf("ReAlloc bigger\n");
    for(nuint i = 0; i < numallocs; i++)
        allocs[i] = CMemory::ReAlloc(allocs[i], allocsize[i] * 2);

    // -- and resize them back down
    printf("ReAlloc smaller\n");
    for(nuint i = 0; i < numallocs; i++)
        allocs[i] = CMemory::ReAlloc(allocs[i], allocsize[i] / 2);

    // -- clean up
    printf("Cleaning up\n");
    for(nuint i = 0; i < numallocs; i++) {
        CMemory::Free(allocs[i]);
        allocs[i] = NULL;
    }

    return 0;
}
