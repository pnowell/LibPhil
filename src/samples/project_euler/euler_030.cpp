// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/assert.h"

// -- constants
static const nuint kAnswer = 443839;

// ================================================================================================
// Problem 30
// ================================================================================================
int32 Problem30() {
    // -- calculate an upper limit
    nuint ninetofive = 9*9*9*9*9;
    nuint max = ninetofive;

    // -- as an upper bound we just want to make sure its greater than its number
    // -- of digits times 9^5
    nuint lastnumdigits;
    nuint numdigits = 0;
    do {
        lastnumdigits = numdigits;
        nuint temp = max;
        numdigits = 0;
        while(temp > 0) {
            temp /= 10;
            ++numdigits;
        }
        if(lastnumdigits != numdigits)
            max = ninetofive * numdigits;
    } while(lastnumdigits != numdigits);

    nuint result = 0;
    for(nuint i = 2; i < max; ++i) {
        
        nuint temp = i;
        nuint sum = 0;
        while(temp > 0) {
            nuint digit = temp % 10;
            temp /= 10;
            sum += digit * digit * digit * digit * digit;
        }
        if(sum == i) {
            printf(NUintFmt_ " ", sum);
            result += sum;
        }
    }

    printf("\nThe sum of those is " NUintFmt_ "\n", result);
    Assert_(result == kAnswer, "The answer should have been " NUintFmt_, kAnswer);

    return 0;
}
