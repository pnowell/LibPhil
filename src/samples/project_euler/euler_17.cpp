// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"

// -- the number of letters it takes to write each number in the ones digit
static const nuint kOnes[] = {
    0,
    3, // one
    3, // two
    5, // three
    4, // four
    4, // five
    3, // six
    5, // seven
    5, // eight
    4, // nine
    3, // ten
    6, // eleven
    6, // twelve
    8, // thirteen
    8, // fourteen
    7, // fifteen
    7, // sixteen
    9, // seventeen
    8, // eighteen
    8, // nineteen
};

// -- the number of letters it takes to write each number in the tens digit
static const nuint kTens[] = {
    0,
    0,
    6, // twenty
    6, // thirty
    5, // forty
    5, // fifty
    5, // sixty
    7, // seventy
    6, // eighty
    6, // ninety
};

static const nuint kHundred = 7;
static const nuint kAnd = 3;
static const nuint kOneThousand = 11;

static const nuint kAnswer = 21124;

// ================================================================================================
// Problem 17
// ================================================================================================
int32 Problem17() {
    // -- get the sum of the numbers from 1 to 9
    nuint to9 = 0;
    for(nuint i = 1; i <= 9; ++i)
        to9 += kOnes[i];

    // -- get the sum of the numbers 10 to 19
    nuint to19 = 0;
    for(nuint i = 10; i <= 19; ++i)
        to19 += kOnes[i];

    // -- get the sum of the numbers from 20 to 99
    nuint to99 = 0;
    for(nuint i = 2; i <= 9; ++i)
        to99 += kTens[i] * 10 + to9;
    
    // -- now get the sum of all the letters from 100 to 999
    nuint to999 = 0;
    for(nuint i = 1; i <= 9; ++i)
        to999 += kHundred * 100 + kOnes[i] * 100 + kAnd * 99 + to9 + to19 + to99;

    printf("Number of letters from 1 to 9 is " NUintFmt_ "\n", to9);
    printf("Number of letters from 10 to 19 is " NUintFmt_ "\n", to19);
    printf("Number of letters from 20 to 99 is " NUintFmt_ "\n", to99);
    printf("Number of letters from 100 to 999 is " NUintFmt_ "\n", to999);

    nuint numletters = to9 + to19 + to99 + to999 + kOneThousand;
    printf("The sum of the number of letters is " NUintFmt_ "\n", numletters);

    Assert_(numletters == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
