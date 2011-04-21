// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "numerics/cprimecalculator.h"

static const uint64 numdivisors = 500;
static const uint64 kAnswer = 76576500;

// ================================================================================================
// Problem 12
// ================================================================================================
int32 Problem12() {
    // -- start at the triangle closest to (and not greater than) numdivisors to save a little time
    //uint64 triidx = (IntSqrt(1 + 8 * numdivisors) - 1) >> 1;
    // -- start off at the triangle number just less than 500
    uint64 triidx = 31;
    uint64 trinum = (triidx * (triidx + 1)) >> 1;
    uint64 trisqrt = 1;
    uint64 product,numprimes,i,temp,currprime,factorpow;

    // -- initialize our prime list
    CPrimeCalculator primecalc;

    do {
        // -- move on to the next triangle number
        ++triidx;
        trinum += triidx;

        // -- fix the triangle number square root
        while(trisqrt * trisqrt <= trinum)
            ++trisqrt;

        // -- iterate finding more primes until we've reached the square root of this number
        primecalc.FindPrimesUpTo(trisqrt);

        // -- and take the product of the powers of each prime factor plus one
        product = 1;
        numprimes = primecalc.NumPrimes();
        temp = trinum;
        for(i = 0; i < numprimes && temp > 1; ++i) {
            currprime = primecalc.Prime(i);
            factorpow = 1;
            while((temp % currprime) == 0) {
                ++factorpow;
                temp = temp / currprime;
            }
            product *= factorpow;
        }

        // -- if we've found a number with more than the required number of divisors, we can stop
    } while(product <= numdivisors);

    printf("%lld (the %lld triangle number) has %lld divisors\n\n", trinum, triidx, product);

    printf("%lld = ", trinum);
    temp = trinum;
    for(i = 0; i < numprimes && temp > 1; ++i) {
        currprime = primecalc.Prime(i);
        factorpow = 0;
        while((temp % currprime) == 0) {
            ++factorpow;
            temp = temp / currprime;
        }
        if(factorpow > 0)
            printf("%lld^%lld ", currprime, factorpow);
    }
    printf("\n");

    /*                        pow     count   factors
     1  :  1 :              : 0     : 1     : 1
     2  :  3 : 3            : 1     : 2     : 1,3
     3  :  6 : 2,3          : 1,1   : 4     : 1,2,3,6
     4  : 10 : 2,5          : 1,1   : 4     : 1,2,5,10
     5  : 15 : 3,5          : 1,1   : 4     : 1,3,5,15
     6  : 21 : 3,7          : 1,1   : 4     : 1,3,7,21
     7  : 28 : 2,2,7        : 2,1   : 6     : 1,2,4,7,14,28
     8  : 35 : 5,7          : 1,1   : 4     : 1,5,7,35
     9  : 44 : 2,2,11       : 2,1   : 6     : 1,2,4,11,22,44
    10  : 54 : 2,3,3,3      : 1,3   : 8     : 1,2,3,6,9,18,27,54
    11  : 65 : 5,13         : 1,1   : 4     : 1,5,13,65
    12  : 77 : 7,11         : 1,1   : 4     : 1,7,11,77
    13  : 90 : 2,3,3,5      : 1,2,1 : 10    : 1,2,3,6,9,10,15,30,45,90

     n = 2^a * 3^b * 5^c * 7^d * 11^e * ...
     number of factors is (a+1)(b+1)(c+1)...
    */

    return 0;
}
