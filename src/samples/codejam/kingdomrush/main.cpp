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

// ------------------------------------------------------------------------------------------------
// Record of a particular level
// ------------------------------------------------------------------------------------------------
struct SLevel {
    uintn req1;
    uintn req2;
    nflag comp1;

    SLevel(uintn r1, uintn r2) : req1(r1), req2(r2), comp1(false) {}
};

// ------------------------------------------------------------------------------------------------
// A pointer to a particular level (so we can have tables of these sorted on different criteria)
// ------------------------------------------------------------------------------------------------
struct SLevelPtr {
    SLevel* lev;
    SLevelPtr(SLevel* l) : lev(l) {}
};

// ------------------------------------------------------------------------------------------------
// Compare function for sorting increasing req1
// ------------------------------------------------------------------------------------------------
struct SByReq1 {
    static intn Compare(SLevelPtr& left, SLevelPtr& right) {
        // -- look for levels with lower "1" requirements first
        if(left.lev->req1 < right.lev->req1)
            return -1;
        if(left.lev->req1 > right.lev->req1)
            return 1;

        return 0;
    }
};

// ------------------------------------------------------------------------------------------------
// Compare function for sorting increasing req2
// ------------------------------------------------------------------------------------------------
struct SByReq2 {
    static intn Compare(SLevelPtr& left, SLevelPtr& right) {
        // -- look for levels with lower "2" requirements first
        if(left.lev->req2 < right.lev->req2)
            return -1;
        if(left.lev->req2 > right.lev->req2)
            return 1;

        return 0;
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

    uint32 numlevs;
    uint32 r1, r2;
    CTable<SLevel> levs;
    CTable<SLevelPtr> byreq1;
    CTable<SLevelPtr> byreq2;
    for(uintn i = 0; i < numtests; ++i) {
        fscanf_s(fp, "%d", &numlevs);
        levs.Clear();
        for(uintn j = 0; j < numlevs; ++j) {
            fscanf_s(fp, "%d %d", &r1, &r2);
            levs.Grow(SLevel(r1, r2));
        }

        // -- fill the three pass tables with pointers to the main table
        byreq1.Clear();
        byreq2.Clear();
        for(uintn j = 0; j < numlevs; ++j) {
            SLevel* lev = levs.GetElem(j);
            byreq1.Grow(SLevelPtr(lev));
            byreq2.Grow(SLevelPtr(lev));
        }

        byreq1.Sort<SByReq1>();
        byreq2.Sort<SByReq2>();

        uint32 result = 0;
        uint32 stars = 0;
        nflag possible = true;
        nflag found;
        uintn numcomplete = 0;
        while(numcomplete < numlevs) {
            // -- look through by increasing req2
            uintn fallback = kNeverIndex;
            found = false;
            uintn j;
            for(j = 0; j < byreq2.Count(); ++j) {
                SLevel& lev = *byreq2[j].lev;
                if(lev.req2 > stars)
                    break;
                else if(lev.comp1)
                    fallback = j;
                else {
                    // -- we found a two-for-one
                    found = true;
                    lev.comp1 = true;
                    ++numcomplete;
                    stars += 2;
                    ++result;

                    DebugLog_("% 4lld Completing (%lld %lld) for both stars\n",
                              stars, lev.req1, lev.req2);

                    byreq2.Remove(j);
                    break;
                }
            }

            // -- if we found something, go back to the first pass
            if(found)
                continue;

            // -- otherwise if we have a fallback, go ahead and use that
            if(fallback < byreq2.Count()) {
                found = true;
                ++numcomplete;
                stars += 1;
                ++result;

                #if DebugLogging_
                    SLevel& lev = *byreq2[fallback].lev;
                    DebugLog_("% 4lld Completing (%lld %lld) for its second star\n",
                              stars, lev.req1, lev.req2);
                #endif

                byreq2.Remove(fallback);
                continue;
            }

            // -- now, we should look through the req1 list to see if there's anything at all
            // -- we can do, and find the one with the highest req2 (least likely to be able to
            // -- get to it in time)
            uintn best = kNeverIndex;
            uintn bestreq = 0;
            for(j = 0; j < byreq1.Count();) {
                SLevel& lev = *byreq1[j].lev;
                if(lev.comp1) {
                    byreq1.Remove(j);
                    continue;
                }
                if(lev.req1 > stars)
                    break;
                if(best == kNeverIndex || lev.req2 > bestreq) {
                    best = j;
                    bestreq = lev.req2;
                }

                ++j;
            }
            if(best != kNeverIndex) {
                SLevel& lev = *byreq1[best].lev;
                found = true;
                lev.comp1 = true;
                stars += 1;
                ++result;

                DebugLog_("% 4lld Completing (%lld %lld) for its first star\n",
                          stars, lev.req1, lev.req2);

                byreq1.Remove(best);
            }

            // -- if we still didn't find anything, quit
            if(!found) {
                possible = false;
                break;
            }
        }

        if(possible)
            Log_("Case #%d: %d\n", i+1, result);
        else
            Log_("Case #%d: Too Bad\n", i+1);
    }

    // -- close the file
    fclose(fp);

    return 0;
}
