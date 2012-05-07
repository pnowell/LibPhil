// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"

// -- constants
static const uintn kNumMonths = 12;
static const uintn kNormalMonths[kNumMonths] = {
    31, // -- Jan
    28, // -- Feb
    31, // -- Mar
    30, // -- Apr
    31, // -- May
    30, // -- Jun
    31, // -- Jul
    31, // -- Aug
    30, // -- Sep
    31, // -- Oct
    30, // -- Nov
    31, // -- Dec
};

static const uintn kLeapMonths[kNumMonths] = {
    31, // -- Jan
    29, // -- Feb
    31, // -- Mar
    30, // -- Apr
    31, // -- May
    30, // -- Jun
    31, // -- Jul
    31, // -- Aug
    30, // -- Sep
    31, // -- Oct
    30, // -- Nov
    31, // -- Dec
};

static const uintn kNumDays = 7;
static const uintn kAnswer = 171;

// ================================================================================================
// Problem 19
// ================================================================================================
int32 Problem19() {
    uintn year = 1901;
    uintn day = 2; // jan 1st 1901 was a Tuesday
   
    uintn numsundays = 0;
    for(; year <= 2000; ++year) {
        nflag leap = (((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0);
        const uintn* months = leap ? kLeapMonths : kNormalMonths;
        for(uintn m = 0; m < kNumMonths; ++m) {
            if(day == 0)
                ++numsundays;

            day += months[m];
            day = day % kNumDays;
        }
    }

    CLog::Write("Num sundays = " NUintFmt_ "\n", numsundays);

    Assert_(numsundays == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}

