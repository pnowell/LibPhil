// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"

// -- system includes
#include <stdio.h>

#define DebugLogging_ 0
#if DebugLogging_
    #define DebugLog_(msg, ...)     Log_(msg, ##__VA_ARGS__)
#else
    #define DebugLog_(msg, ...)     ((void)0)
#endif

struct SItem {
    uintn count;
    uintn type;

    SItem(uintn c, uintn t) : count(c), type(t) {}
};

struct SState {
    uintn boxseq;
    uintn boxdone;
    uintn toyseq;
    uintn toydone;
    uintn completed;

    SState(uintn a, uintn b, uintn c, uintn d, uintn e)
        : boxseq(a), boxdone(b), toyseq(c), toydone(d), completed(e) {}
};

uintn Compute(CTable<SItem>& boxes, CTable<SItem>& toys) {
    uintn best = 0;

    CTable<SState> stack;
    stack.Grow(SState(0, 0, 0, 0, 0));

    while(stack.Count() > 0) {
        uintn stateidx = stack.Count() - 1;
        SState state = stack[stateidx];
        stack.Remove(stateidx);

        // -- check for a finish condition
        if(state.boxseq >= boxes.Count() || state.toyseq >= toys.Count()) {
            // -- check to see if this is a better outcome
            if(state.completed > best)
                best = state.completed;
            continue;
        }

        SItem& box = boxes[state.boxseq];
        SItem& toy = toys[state.toyseq];
        if(box.type == toy.type) {
            uintn boxremain = box.count - state.boxdone;
            uintn toyremain = toy.count - state.toydone;
            uintn min = boxremain < toyremain ? boxremain : toyremain;
            state.completed += min;

            if(boxremain == min) {
                ++state.boxseq;
                state.boxdone = 0;
            }
            else
                state.boxdone += min;

            if(toyremain == min) {
                ++state.toyseq;
                state.toydone = 0;
            }
            else
                state.toydone += min;

            // -- push this state back on to cointnue
            stack.Grow(state);
        }
        else {
            // -- we can do one of two things, either throw away the current string of boxes or the
            // -- current string of toys
            SState option1 = state;
            ++option1.boxseq;
            option1.boxdone = 0;
            stack.Grow(option1);

            SState option2 = state;
            ++option2.toyseq;
            option2.toydone = 0;
            stack.Grow(option2);
        }
    }

    return best;
}

struct STest {
    CDataPtr<uint64> testing;
    uint64 pointto;
};

// ================================================================================================
// Main
// ================================================================================================
int main(sint32 argc, sint8* argv[]) {
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

    CTable<SItem> boxes;
    CTable<SItem> toys;
    for(uintn i = 0; i < numtests; ++i) {
        uintn n, m;
        fscanf_s(fp, "%lld %lld", &n, &m);

        boxes.Clear();
        toys.Clear();

        for(uintn j = 0; j < n; ++j) {
            uintn num, type;
            fscanf_s(fp, "%lld %lld", &num, &type);
            boxes.Grow(SItem(num, type));
        }

        for(uintn j = 0; j < m; ++j) {
            uintn num, type;
            fscanf_s(fp, "%lld %lld", &num, &type);
            toys.Grow(SItem(num, type));
        }

        uintn completed = Compute(boxes, toys);
        Log_("Case #%d: %lld\n", i+1, completed);
    }

    // -- close the file
    fclose(fp);

    return 0;
}
