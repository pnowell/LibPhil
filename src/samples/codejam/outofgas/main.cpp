// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"
#include "numerics/cmath.h"

// -- system includes
#include <stdio.h>

#define DebugLogging_ 0
#if DebugLogging_
    #define DebugLog_(msg, ...)     Log_(msg, ##__VA_ARGS__)
#else
    #define DebugLog_(msg, ...)     ((void)0)
#endif

// ------------------------------------------------------------------------------------------------
// Represents a single position data point for the other car
// ------------------------------------------------------------------------------------------------
struct SPos {
    real64 t;
    real64 x;

    SPos(real64 t_, real64 x_) : t(t_), x(x_) {}
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

    CTable<SPos> car;
    for(uintn i = 0; i < numtests; ++i) {
        real64 dist;
        uintn n, a;
        fscanf_s(fp, "%Lf %lld %lld", &dist, &n, &a);

        car.Clear();
        for(uintn j = 0; j < n; ++j) {
            real64 t, x;
            fscanf_s(fp, "%Lf %Lf", &t, &x);

            // -- if we go past our home distance, clamp to that
            if(x > dist) {
                if(j > 0) {
                    real64 pt = car[j-1].t;
                    real64 px = car[j-1].x;
                    real64 dt = t - pt;
                    real64 dx = x - px;
                    t = pt + (dt/dx) * (dist - px);
                }
                x = dist;
            }

            // -- put that in the car's data
            car.Grow(SPos(t, x));
        }

        // -- go back through the car positions, and reduce it to a convex hull
        nflag founddip = true;
        while(founddip) {
            founddip = false;
            for(uintn j = 1; j < car.Count()-1;) {
                // -- check to see if this point is a dip
                SPos& last = car[j-1];
                SPos& curr = car[j];
                SPos& next = car[j+1];
                real64 oldvel = (curr.x - last.x) / (curr.t - last.t);
                real64 newvel = (next.x - curr.x) / (next.t - curr.t);
                if(newvel <= oldvel) {
                    car.Remove(j);
                    founddip = true;
                }
                else
                    ++j;
            }
        }
        n = car.Count();

        Log_("Case #%d:\n", i+1);

        for(uintn j = 0; j < a; ++j) {
            real64 accel;
            fscanf_s(fp, "%Lf", &accel);

            // -- go through the car positions and find the one that offsets our curve the most
            real64 falltime = CMath::Sqrt(2 * dist / accel);
            real64 offset = 0.0;
            for(uintn k = 0; k < n; ++k) {
                SPos& curr = car[k];
                // -- get how long it would take to fall to this point
                real64 colltime = CMath::Sqrt(2 * curr.x / accel);
                // -- if that's sooner that the car is at this point, delay our initial fall
                // -- by the difference
                if(colltime < curr.t && offset < curr.t - colltime)
                    offset = curr.t - colltime;
            }

            Log_("%.6Lf\n", falltime + offset);
        }
    }

    // -- close the file
    fclose(fp);

    return 0;
}
