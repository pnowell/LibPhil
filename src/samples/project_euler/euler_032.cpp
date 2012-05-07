// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"
#include "io/clog.h"

// -- constants
static const uintn kAllNine = 0x3fe;
static const uintn kAnswer = 45228;

// -- all products that satisfy the conditions can be written as
// -- a x bcde = fghi
// -- ab x cde = fghi
// -- because the following are not possible
// -- a x bcd = efghi
// -- ab x cd = efghi
// -- abc x def = ghi

// ------------------------------------------------------------------------------------------------
// Iterate over all the possible multipliers for the given multiplicand
// ------------------------------------------------------------------------------------------------
static void FindProducts(uintn a, uintn digitbits, CTable<uintn>& products) {
    uintn min = 1234 / a;
    uintn max = 9876 / a;

    // -- if a is a single digit, then the second operand needs to be 4 digits
    if(a < 10 && min < 1234)
        min = 1234;

    // -- if a is double digit, then the second operand needs to be 3 digits
    if(a >= 10) {
        if(min < 123)
            min = 123;
        if(max > 987)
            max = 987;
    }

    // -- if we've already ruled out the possibility of any results, just return
    if(max < min)
        return;

    // -- get the digits for the min, and then iterate up through the max
    uintn digits[4];
    uintn curr = min - 1;
    for(uintn i = 0; i < 4; ++i) {
        digits[i] = curr % 10;
        curr /= 10;
    }

    // -- now iterate until we reach max
    curr = min - 1;
    while(curr <= max) {
        // -- look until we see a number with digits that don't overlap with the input
        nflag illegal = true;
        uintn currbits = digitbits;
        while(illegal) {
            // -- increment the ones digit
            ++digits[0];
            if(digits[0] > 9) {
                digits[0] = 1;
                ++digits[1];
                if(digits[1] > 9) {
                    digits[1] = 1;
                    ++digits[2];
                    if(digits[2] > 9) {
                        digits[2] = 1;
                        ++digits[3];
                    }
                }
            }

            // -- first update curr to be the new value
            curr = digits[0] + digits[1]*10 + digits[2]*100 + digits[3]*1000;
            if(curr > max)
                return;

            // -- then check the current digits to see if they are worth checking
            currbits = digitbits;
            illegal = false;
            for(uintn i = 0; i < 4 && !illegal; ++i) {
                // -- if we're zero and a higher digit is not zero (we're not a leading zero)
                // -- then this is an invalid number
                if(digits[i] == 0) {
                    if(i+1 < 4 && digits[i+1] != 0) {
                        illegal = true;
                        break;
                    }
                }
                else {
                    // -- if this digit has already been done, keep looking
                    if((currbits & (uintn(1) << digits[i])) != 0) {
                        illegal = true;
                        break;
                    }
                    // -- record this digit in the current bits
                    currbits = currbits | uintn(1) << digits[i];
                }
            }
        }

        uintn product = a * curr;

        // -- then look at each digit
        illegal = false;
        while(product > 0) {
            uintn digit = product % 10;
            product /= 10;

            // -- check to see if it's zero
            if(digit == 0) {
                illegal = true;
                break;
            }
            if((currbits & (uintn(1) << digit)) != 0) {
                illegal = true;
                break;
            }
            currbits = currbits | (uintn(1) << digit);
        }

        // -- if it's not illegal and we've found each digit from 1 to 9
        if(!illegal && currbits == kAllNine) {
            product = a * curr;

            // -- look through the existing products, and make sure it's not already there
            uintn count = products.Count();
            uintn i = 0;
            for(; i < count; ++i) {
                if(products[i] == product)
                    break;
            }
            if(i == count)
                products.Grow(product);
            else
                CLog::Write("-repeat- ");

            CLog::Write(UintNFmt_ " x " UintNFmt_ " = " UintNFmt_ "\n", a, curr, product);
        }
    }
}

// ================================================================================================
// Problem 32
// ================================================================================================
int32 Problem32() {
    CTable<uintn> products;

    // -- first handle single digit numbers
    // -- one can't work, because it would result in identical multiplier and product
    for(uintn i = 2; i <= 9; ++i)
        FindProducts(i, uintn(1) << i, products);

    // -- then double digit numbers
    for(uintn i = 1; i <= 9; ++i) {
        for(uintn j = 1; j <= 9; ++j) {
            if(i == j)
                continue;

            FindProducts(i*10 + j, uintn(1) << i | uintn(1) << j, products);
        }
    }

    // -- add all the products we collected in our table
    uintn result = 0;
    uintn count = products.Count();
    for(uintn i = 0; i < count; ++i)
        result += products[i];

    CLog::Write("The sum of the products is " UintNFmt_ "\n", result);
    Assert_(result == kAnswer, "The answer should have been " UintNFmt_, kAnswer);

    return 0;
}
