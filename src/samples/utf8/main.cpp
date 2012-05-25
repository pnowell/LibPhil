// -- libs includes
#include "containers/cstringutf8.h"

// -- system includes
#include <stdio.h>

const uint8 testarray[] = {
    0xe5, 0x8d, 0x83, 0xe4, 0xbd, 0xb3, 0xe3, 0x82,
    0x92, 0xe6, 0x84, 0x9b, 0xe3, 0x81, 0x97, 0xe3,
    0x81, 0xa6, 0xe3, 0x81, 0x84, 0xe3, 0x81, 0xbe,
    0xe3, 0x81, 0x99, 0xe3, 0x82, 0x88, 0xe3, 0x80,
    0x82, 0x00
};

// ================================================================================================
// Main
// ================================================================================================
int main(sint32 argc, sint8* argv[]) {
    CStringUTF8 test((cpointer)testarray);

    // -- make sure we're given a file name
    if(argc < 2)
        return 0;

    // -- try to open it
    FILE* fp = NULL;
    fopen_s(&fp, argv[1], "wb");
    fputs(test.GetString(), fp);
    fclose(fp);

    return 0;
}
