// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "core/utils.h"
#include "containers/ctable.h"
#include "numerics/cmath.h"
#include "io/clog.h"

static const uintn kTri[] = {
                                75,
                              95, 64,
                            17, 47, 82,
                          18, 35, 87, 10,
                        20,  4, 82, 47, 65,
                      19,  1, 23, 75,  3, 34,
                    88,  2, 77, 73,  7, 63, 67,
                  99, 65,  4, 28,  6, 16, 70, 92,
                41, 41, 26, 56, 83, 40, 80, 70, 33,
              41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
            53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
          70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
        91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
      63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
     4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23,
};
static const uintn kSize = ArraySize_(kTri);
static const uintn kAnswer = 1074;

// -- macro to turn row,col into a single index
#define Idx_(r, c) (((r) * ((r) + 1)) / 2 + (c))

// ================================================================================================
// Do all the work for problem 18 and 67
// ================================================================================================
sint32 Problem18And67(const uintn* tri, uintn size, uintn answer) {
    uintn height = (CMath::ISqrt(1 + 8*size) - 1) / 2;
    Assert_(height * (height + 1) / 2 == size, "Are you sure the size you passed in is correct?");
    Assert_(height > 1, "Really?  Why bother with such a small triangle size");

    // -- make a temporary table with a copy of the triangle
    CTable<uintn> maxpaths;
    for(uintn i = 0; i < size; ++i)
        maxpaths.Grow(tri[i]);

    // -- start from the second to last row
    for(uintn i = height-1; i > 0;) {
        --i;

        // -- for every element, choose from the two below it which will make a bigger
        // -- total, and add that into the current spot
        for(uintn j = 0; j <= i; ++j) {
            uintn left = maxpaths[Idx_(i+1, j)];
            uintn right = maxpaths[Idx_(i+1, j+1)];
            if(left > right)
                maxpaths[Idx_(i, j)] += left;
            else
                maxpaths[Idx_(i, j)] += right;
        }
    }

    CLog::Write("The maximum total is " UintNFmt_ "\n", maxpaths[0]);
    Assert_(maxpaths[0] == answer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}

// ================================================================================================
// Problem 18
// ================================================================================================
sint32 Problem18() {
    return Problem18And67(kTri, kSize, kAnswer);
}
