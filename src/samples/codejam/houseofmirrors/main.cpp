// -- libs includes
#include "core/types.h"
#include "io/clog.h"
#include "containers/ctable.h"
#include <stdio.h>

#define DebugOutput_ (0)

// ------------------------------------------------------------------------------------------------
// Struct for storing the layout of the room .. for the "short" version of the problem only =(
// ------------------------------------------------------------------------------------------------
struct SLayout {
    nuint h;
    nuint w;
    nuint d;
    nint x;
    nint y;
};

// ------------------------------------------------------------------------------------------------
// Struct for storing a slope as 2 integers (keep out of floating point land)
// ------------------------------------------------------------------------------------------------
struct SSlope {
    nint neg;
    nint dx;
    nint dy;

    // -- constructor
    SSlope(nint x, nint y) {
        if((y == 0 && x < 0) || y < 0) {
            dx = -x;
            dy = -y;
            neg = 1;
        }
        else {
            dx = x;
            dy = y;
            neg = 0;
        }
    }

    // -- comparison
    static nint Compare(SSlope left, SSlope right) {
        nint det = left.dy * right.dx - left.dx * right.dy;
        // -- if the determinant isn't zero, we already know we have different slopes
        if(det != 0)
            return det;

        // -- otherwise base the order off of the number of sign bits the two have set
        return right.neg - left.neg;
    }
};
// ------------------------------------------------------------------------------------------------
// Read a line and get rid of the newline characters at the end
// ------------------------------------------------------------------------------------------------
void GetLine(FILE* fp, pointer line, nuint size) {
    fgets(line, int(size), fp);
    for(nuint i = 0; i < size; ++i) {
        if(line[i] == 0)
            return;
        if(line[i] == '\n' || line[i] == '\r') {
            line[i] = 0;
            return;
        }
    }
}

// ------------------------------------------------------------------------------------------------
// Parse the layout for one test
// ------------------------------------------------------------------------------------------------
void ParseLayout(FILE* fp, SLayout& layout) {
    fscanf_s(fp, "%lld %lld %lld", &layout.h, &layout.w, &layout.d);

    const nuint linesize = 64;
    int8 line[linesize];

    // -- finish the previous line
    GetLine(fp, line, linesize);

    // -- read the first row
    GetLine(fp, line, linesize);

    // -- read the middle rows
    nflag found = false;
    for(nuint i = 1; i < layout.h-1; ++i) {
        GetLine(fp, line, linesize);

        // -- read the middle
        for(nuint j = 1; found == false && j < layout.w-1; ++j) {
            if(line[j] == 'X') {
                // -- the position is understood to be at a ?.5 position on the x and y
                // -- but we store the floor of that number (just to keep things in integers)
                layout.x = j-1;
                layout.y = i-1;
                found = true;
            }
        }
    }

    // -- read the last row
    GetLine(fp, line, linesize);

    // -- adjust the width and height to be the observable width/height inside the mirrors
    layout.w -= 2;
    layout.h -= 2;
}

// ------------------------------------------------------------------------------------------------
// Utility for getting the nth reflected position in a particular dimension
// ------------------------------------------------------------------------------------------------
nint ReflectedCoord(nint n, nint original, nuint len) {
    if((n & 1) == 0)
        return len * n + original;

    nint k = (n + 1) / 2;
    return 2 * len * k - 1 - original;
}

// ------------------------------------------------------------------------------------------------
// Compute the number of reflections for the given layout
// ------------------------------------------------------------------------------------------------
nuint NumReflections(SLayout& layout) {
    nuint result = 0;

    // -- we'll keep a sorted table of slopes
    CTable<SSlope> slopes;

    // -- laying out a grid of reflected rooms, how many rooms should we do in any direction to
    // -- make sure we're looking at enough?
    // -- 2 reflections will always displace you by twice that dimension, so let's just go with
    // -- d / dim rounded up to the nearest even number
    // $$$ Something is wrong here, so I added more checks
    // $$$ Not sure how wrong it is, probably off by 1
    nint refx = (2 * layout.d / layout.w + 1) / 2 + 3;
    nint refy = (2 * layout.d / layout.h + 1) / 2 + 3;
    nint dsqr = layout.d * layout.d;
    #if DebugOutput_
        CLog::Write("pos x=%lld, pos y=%lld, Max dsqr=%lld\n", layout.x, layout.y, dsqr);
    #endif
    for(nint nx = -refx; nx <= refx; ++nx) {
        nint x = ReflectedCoord(nx, layout.x, layout.w);
        nint dispx = layout.x - x;
        nint dispxsqr = dispx * dispx;
        for(nint ny = -refy; ny <= refy; ++ny) {
            // -- we don't count our real self
            if(nx == 0 && ny == 0)
                continue;

            nint y = ReflectedCoord(ny, layout.y, layout.h);
            nint dispy = layout.y - y;
            nint dispysqr = dispy * dispy;

            #if DebugOutput_
                CLog::Write("nx=%lld, ny=%lld, x=%lld, y=%lld", nx, ny, x, y);
            #endif

            // -- if this image is closer than d, we can see it
            #if DebugOutput_
                CLog::Write(", dsqr=%lld", dispxsqr + dispysqr);
            #endif
            if(dispxsqr + dispysqr <= dsqr) {
                // -- now check to see if this is in the table of slopes
                SSlope newslope(dispx, dispy);
                nuint index;
                if(!slopes.Search<SSlope>(newslope, index)) {
                    // -- insert it into the table of slopes
                    slopes.Insert(index, newslope);
                    ++result;

                    #if DebugOutput_
                        CLog::Write(" <--");
                    #endif
                }

                #if DebugOutput_
                    else {
                        CLog::Write(" SLOPE COL");
                    }
                #endif
            }

            #if DebugOutput_
                CLog::Write("\n");
            #endif
        }
    }

    #if DebugOutput_
        nuint count = slopes.Count();
        CLog::Write("##################\n");
        for(nuint i = 0; i < count; ++i) {
            SSlope& s = slopes[i];
            CLog::Write("    dx=%lld dy=%lld neg=%lld\n", s.dx, s.dy, s.neg);
        }
    #endif

    return result;
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

    // -- iterate over all the tests
    for(nuint i = 0; i < numtests; ++i) {
        SLayout layout;
        ParseLayout(fp, layout);
        nuint result = NumReflections(layout);
        CLog::Write("Case #%lld: %lld\n", i+1, result);
    }

    // -- close the file
    fclose(fp);

    return 0;
}
