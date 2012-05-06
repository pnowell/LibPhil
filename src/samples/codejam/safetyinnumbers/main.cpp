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

struct SPerson {
    uint32 points;
    uint32 index;
    real64 min;

    SPerson(uint32 p, uint32 i) : points(p), index(i), min(0.0f) {}
};

struct SByPoints {
    static nint Compare(SPerson& a, SPerson& b) {
        return (a.points < b.points) ? -1 : (a.points > b.points) ? 1 : 0;
    }
};

struct SByIndex {
    static nint Compare(SPerson& a, SPerson& b) {
        return (a.index < b.index) ? -1 : (a.index > b.index) ? 1 : 0;
    }
};

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

    CTable<SPerson> people;
    for(nuint i = 0; i < numtests; ++i) {
        people.Clear();
        uint32 total = 0;
        uint32 numpeople;
        fscanf_s(fp, "%d", &numpeople);
        for(nuint j = 0; j < numpeople; ++j) {
            uint32 pnt;
            fscanf_s(fp, "%d", &pnt);
            people.Grow(SPerson(pnt, uint32(j)));
            total += pnt;
        }

        // -- sort the people by point value
        people.Sort<SByPoints>();

        // -- start with the lowest and add enough to make it equal to the next
        // -- then add enough to both to make them both equal to the third
        // -- continue until all the crowd votes are gone
        real64 remaining = 1.0f;
        real64 watermark = real64(people[0].points);
        DebugLog_("Watermark : %Lf\n", watermark);
        nflag usedup = false;
        for(nuint j = 1; j < numpeople && !usedup; ++j) {
            // -- how much do we need to add to all the people so far to get the watermark
            // -- up to the current entry
            real64 diff = (real64(people[j].points) - watermark) * real64(j) / real64(total);
            watermark = real64(people[j].points);

            DebugLog_("Next person %Lf, diff %Lf (%Lf), remaining %Lf\n",
                      real64(people[j].points), diff, diff * real64(total), remaining);

            if(diff > remaining) {
                diff = remaining;
                usedup = true;
            }

            remaining -= diff;

            // -- add that to the minimum for all the people before me
            diff = diff / real64(j);
            DebugLog_("Adjusted diff %Lf, remaining %Lf\n", diff, remaining);
            DebugLog_("People :");
            for(nuint k = 0; k < j; ++k) {
                people[k].min += diff;
                DebugLog_(" %Lf", people[k].min);
            }
            DebugLog_("\n\n");
        }

        if(!usedup) {
            remaining = remaining / real64(numpeople);
            DebugLog_("Average remaining %Lf\nPeople :", remaining);
            for(nuint k = 0; k < numpeople; ++k) {
                people[k].min += remaining;
                DebugLog_(" %Lf", people[k].min);
            }
            DebugLog_("\n");
        }

        // -- sort the people back into their original order
        people.Sort<SByIndex>();

        Log_("Case #%d:", i+1);
        for(nuint j = 0; j < numpeople; ++j)
            Log_(" %.6Lf", people[j].min * 100.0f);
        Log_("\n");
    }

    // -- close the file
    fclose(fp);

    return 0;
}
