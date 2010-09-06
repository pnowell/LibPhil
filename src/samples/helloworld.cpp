// -- libs includes
#include "core/types.h"

// -- system includes
#include <stdio.h>

#define ShowSize_(TYPE) printf("The size of " #TYPE " is %d\n", sizeof(TYPE))

nint main(nint argc, int8* argv[]) {
    ShowSize_(nint);
    ShowSize_(unint);
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

    return 0;
}
