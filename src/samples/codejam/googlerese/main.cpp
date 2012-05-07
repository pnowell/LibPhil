// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"
#include <stdio.h>

// -- the remap
cpointer kDict = "yhesocvxduiglbkrztnwjpfmaq";

// ------------------------------------------------------------------------------------------------
// Check if this is a valid string character
// ------------------------------------------------------------------------------------------------
nflag IsStringChar(intn c) {
    return c == ' ' || (c >= 'a' && c <= 'z');
}

// ================================================================================================
// Main
// ================================================================================================
int main(int32 argc, int8* argv[]) {
    // -- make sure we're given a file name
    if(argc < 2) {
        CLog::Write("You need to give me a filename, please\n");
        return 0;
    }

    // -- try to open it
    FILE* fp = NULL;
    fopen_s(&fp, argv[1], "r");

    // -- make sure we could open it
    if(fp == NULL) {
        CLog::Write("Don't know that file\n");
        return 0;
    }

    // -- read stuff
    uint32 numtests;
    fscanf_s(fp, "%d", &numtests);

    intn c = fgetc(fp);
    while(IsStringChar(c) == false && c != EOF)
        c = fgetc(fp);

    // -- now read one character at a time
    uintn testidx = 0;
    while(testidx < numtests && c != EOF) {
        ++testidx;
        CLog::Write("Case #%d: ", testidx);

        while(IsStringChar(c) && c != EOF) {
            if(c == ' ')
                CLog::Write(" ");
            else
                CLog::Write("%c", kDict[c - 'a']);
            c = fgetc(fp);
        }

        CLog::Write("\n");

        while(IsStringChar(c) == false && c != EOF)
            c = fgetc(fp);
    }

    // -- close the file
    fclose(fp);

    return 0;
}
