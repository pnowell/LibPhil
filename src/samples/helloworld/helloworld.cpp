// -- libs includes
#include "core/types.h"
#include "core/cmemory.h"
#include "io/clog.h"

// -- useful macro to show the size of a type
#define ShowSize_(TYPE) CLog::Write("The size of " #TYPE " is %d\n", sizeof(TYPE))

// ================================================================================================
// Main
// ================================================================================================
int main(int32 argc, int8* argv[]) {
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
    CLog::Write("Making initial allocations\n");
    for(nuint i = 0; i < numallocs; i++)
        allocs[i] = CMemory::Alloc(allocsize[i]);

    // -- now resize those
    CLog::Write("ReAlloc bigger\n");
    for(nuint i = 0; i < numallocs; i++)
        allocs[i] = CMemory::ReAlloc(allocs[i], allocsize[i] * 2);

    // -- and resize them back down
    CLog::Write("ReAlloc smaller\n");
    for(nuint i = 0; i < numallocs; i++)
        allocs[i] = CMemory::ReAlloc(allocs[i], allocsize[i] / 2);

    // -- clean up
    CLog::Write("Cleaning up\n");
    for(nuint i = 0; i < numallocs; i++) {
        CMemory::Free(allocs[i]);
        allocs[i] = NULL;
    }

    return 0;
}
