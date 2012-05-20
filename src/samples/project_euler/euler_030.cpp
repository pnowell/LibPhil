// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "io/clog.h"

// -- constants
static const uintn kAnswer = 443839;

// ================================================================================================
// Problem 30
// ================================================================================================
sint32 Problem30() {
    // -- calculate an upper limit
    uintn ninetofive = 9*9*9*9*9;
    uintn max = ninetofive;

    // -- as an upper bound we just want to make sure its greater than its number
    // -- of digits times 9^5
    uintn lastnumdigits;
    uintn numdigits = 0;
    do {
        lastnumdigits = numdigits;
        uintn temp = max;
        numdigits = 0;
        while(temp > 0) {
            temp /= 10;
            ++numdigits;
        }
        if(lastnumdigits != numdigits)
            max = ninetofive * numdigits;
    } while(lastnumdigits != numdigits);

    uintn result = 0;
    for(uintn i = 2; i < max; ++i) {
        
        uintn temp = i;
        uintn sum = 0;
        while(temp > 0) {
            uintn digit = temp % 10;
            temp /= 10;
            sum += digit * digit * digit * digit * digit;
        }
        if(sum == i) {
            CLog::Write(UintNFmt_ " ", sum);
            result += sum;
        }
    }

    CLog::Write("\nThe sum of those is " UintNFmt_ "\n", result);
    Assert_(result == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}
