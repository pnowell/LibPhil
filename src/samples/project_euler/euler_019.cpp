// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"

// -- constants
static const nuint kNumMonths = 12;
static const nuint kNormalMonths[kNumMonths] = {
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

static const nuint kLeapMonths[kNumMonths] = {
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

static const nuint kNumDays = 7;

static cpointer kMonthNames[kNumMonths] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec",
};

static cpointer kDayNames[kNumDays] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
};

static const nuint kAnswer = 171;

// ================================================================================================
// Problem 19
// ================================================================================================
int32 Problem19() {
    nuint year = 1901;
    nuint day = 2; // jan 1st 1901 was a Tuesday
   
    nuint numsundays = 0;
    for(; year <= 2000; ++year) {
        nflag leap = (((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0);
        const nuint* months = leap ? kLeapMonths : kNormalMonths;
        for(nuint m = 0; m < kNumMonths; ++m) {
            if(day == 0)
                ++numsundays;

            day += months[m];
            day = day % kNumDays;
        }
    }

    printf("Num sundays = " NUintFmt_ "\n", numsundays);

    Assert_(numsundays == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}

