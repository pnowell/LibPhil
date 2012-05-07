// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"
#include <stdio.h>

#define DebugLogging_ 0
#if DebugLogging_
    #define DebugLog_(msg, ...)     Log_(msg, ##__VA_ARGS__)
#else
    #define DebugLog_(msg, ...)     ((void)0)
#endif

struct SClass {
    CTable<SClass*> derived;
    uintn visited;

    SClass() : derived(), visited(kNeverIndex) {}
};

nflag Trace(SClass* c, uintn idx) {
    CTable<SClass*> stack;
    stack.Grow(c);

    while(stack.Count() > 0) {
        SClass* curr = stack[0];
        stack.Remove(0);

        if(curr->visited == idx)
            return true;
        curr->visited = idx;

        for(uintn i = 0; i < curr->derived.Count(); ++i)
            stack.Grow(curr->derived[i]);
    }

    return false;
}

// ================================================================================================
// Main
// ================================================================================================
int main(int32 argc, int8* argv[]) {
    // -- make sure we're given a file name
    if(argc < 2) {
        Log_("You need to give me a filename, please\n");
        return 0;
    }

    // -- try to open it
    FILE* fp = NULL;
    fopen_s(&fp, argv[1], "r");

    // -- make sure we could open it
    if(fp == NULL) {
        Log_("Don't know that file\n");
        return 0;
    }

    // -- read stuff
    uint32 numtests;
    fscanf_s(fp, "%d", &numtests);

    CTable<SClass> classes;
    for(uintn i = 0; i < numtests; ++i) {
        uintn numclasses;
        fscanf_s(fp, "%lld", &numclasses);
        classes.Clear();
        classes.GrowMultiple(numclasses);
        for(uintn j = 0; j < numclasses; ++j) {
            SClass& curr = classes[j];
            uintn numderived;
            fscanf_s(fp, "%lld", &numderived);
            for(uintn k = 0; k < numderived; ++k) {
                uintn idx;
                fscanf_s(fp, "%lld", &idx);
                // -- connect the classes
                SClass& parent = classes[idx-1];
                curr.derived.Grow(&parent);
            }
        }

        // -- now go through each class tracing all the parents looking for a place we touch twice
        nflag found = false;
        for(uintn j = 0; j < numclasses; ++j) {
            SClass* curr = &classes[j];
            found = Trace(curr, j);
            if(found)
                break;
        }

        Log_("Case #%d: ", i+1);
        if(found)
            Log_("Yes");
        else
            Log_("No");
        Log_("\n");
    }

    // -- close the file
    fclose(fp);

    return 0;
}
