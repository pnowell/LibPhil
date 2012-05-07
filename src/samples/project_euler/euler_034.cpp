// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"
#include "containers/ctable.h"

// -- constants
static const uintn kAnswer = 40730;

// ================================================================================================
// Problem 34
// ================================================================================================
int32 Problem34() {
    const uintn factorial[10] = {
        1,
        1,
        1 * 2,
        1 * 2 * 3,
        1 * 2 * 3 * 4,
        1 * 2 * 3 * 4 * 5,
        1 * 2 * 3 * 4 * 5 * 6,
        1 * 2 * 3 * 4 * 5 * 6 * 7,
        1 * 2 * 3 * 4 * 5 * 6 * 7 * 8,
        1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9,
    };

    // -- first we notice that there will be some number 999... that will given an upper bound
    // -- to these types of numbers (since 9! + 9! + ... doesn't grow as fast as 999... there
    // -- will be a pointt where 9999... will overtake it)
    uintn maxdigits = 1;
    uintn currnumber = 9;
    uintn value = factorial[9];
    while(currnumber < value) {
        currnumber = currnumber * 10 + 9;
        value += factorial[9];
        ++maxdigits;
    }
    CLog::Write("Upper bound is " NUintFmt_ " (greater than its factorial sum " NUintFmt_ ")\n\n",
                currnumber, value);

    // -- non-recursively iterate through all the possibilities of ordered combinations of digits
    // -- then we'll see what sum it comes up with, sort that number's digits and see if it
    // -- matches the ordered list of digits we used to build it
    CTable<uintn> numbers;
    CTable<uintn> digits;

    // -- make a table with enough slots to use
    CTable<uintn> check;

    // -- keep a couple of other variables on the stack
    uintn checkcount, decomp, i;

    // -- start the iteration
    digits.Grow(0);
    value = factorial[0];
    while(digits.Count() > 0) {
        // -- iterate to the next number to try
        if(digits.Count() < maxdigits) {
            // -- just extend the number with the same digit
            uintn togrow = digits[digits.Count() - 1];
            digits.Grow(togrow);
            value += factorial[togrow];
        }
        else {
            // -- start with the last digit
            uintn curr = maxdigits-1;
            // -- increment the digit, and if it overflows, remove it
            value -= factorial[digits[curr]];
            while(digits.Count() > 0 && ++digits[curr] == 10) {
                digits.Remove(curr);
                if(curr > 0)
                    value -= factorial[digits[--curr]];
            }

            if(digits.Count() == 0)
                break;

            value += factorial[digits[curr]];
        }

        // -- check to see if the current number could work
        decomp = value;
        check.Clear();
        while(decomp > 0) {
            check.Grow(decomp % 10);
            decomp /= 10;
        }

        // -- at this point if the number of digits doesn't match, keep looking
        checkcount = check.Count();
        if(checkcount != digits.Count())
            continue;

        // -- sort check
        check.Sort<CompareBasicTypes<uintn> >();

        // -- then check for complete equality with digits
        for(i = 0; i < checkcount && check[i] == digits[i]; ++i);

        // -- if we made it through all the digits, we have a match
        if(i == checkcount) {
            numbers.Grow(value);

            // -- print them out as we find them
            CLog::Write("Found a match " NUintFmt_ "\n", value);
            decomp = value;
            check.Clear();
            while(decomp > 0) {
                check.Grow(decomp % 10);
                decomp /= 10;
            }
            for(; i > 0; --i) {
                CLog::Write("    " NUintFmt_ " : " NUintFmt_ "\n",
                            check[i-1], factorial[check[i-1]]);
            }
            CLog::Write("\n");
        }
    }

    // -- sort numbers
    numbers.Sort<CompareBasicTypes<uintn> >();

    // -- remove the first two trivial matches
    Assert_(numbers[0] == 1 && numbers[1] == 2, "We were expecting two trivial matches");
    CLog::Write("Removing trivial matches 1 and 2\n\n");
    numbers.RemoveMultiple(0, 2);

    // -- compute the sum
    uintn sum = 0;
    uintn count = numbers.Count();
    for(uintn i = 0; i < count; ++i)
        sum += numbers[i];
    CLog::Write("The sum is " NUintFmt_ "\n", sum);

    Assert_(sum == kAnswer, "The answer should have been " NUintFmt_, kAnswer);
    
    return 0;
}
