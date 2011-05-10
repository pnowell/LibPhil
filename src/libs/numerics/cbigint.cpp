// -- libs includes
#include "numerics/cbigint.h"

// ================================================================================================
// Constructors
// ================================================================================================
CBigInt::CBigInt(nuint val) : limit(0) {
    while(val > 0) {
        digits.Grow(uint8(val % 10));
        val /= 10;
    }
}

CBigInt::CBigInt(cpointer v) : limit(0) {
    // -- find the length of the number
    nuint len = 0;
    while(v[len] != 0)
        ++len;

    if(len > 0) {
        digits.GrowMultiple(len);

        for(nuint i = 0; i < len; ++i) {
            uint8 curr = v[len - 1 - i];
            Assert_('0' <= curr && curr <= '9', "'%c' is not a numeric digit", curr);
            digits[i] = curr - '0';
        }
    }
}

// ================================================================================================
// Allow the user to only care about a certain number of least significant digits
// ================================================================================================
void CBigInt::SetDigitLimit(nuint lim) {
    limit = lim;

    nuint numdigits = digits.Count();
    if(numdigits > limit)
        digits.RemoveMultiple(limit, numdigits - limit);
}

// ================================================================================================
// Clear the digit limitation
// ================================================================================================
void CBigInt::ClearDigitLimit() {
    limit = 0;
}

// ================================================================================================
// Assignment operators
// ================================================================================================
const CBigInt& CBigInt::operator=(const CBigInt& other) {
    // -- clear our digits
    digits.Clear();

    // -- get the other number's digit count and limit it if necessary
    nuint numdigits = other.NumDigits();
    if(limit > 0 && numdigits > limit)
        numdigits = limit;

    // -- give ourselves the right number of digits, and copy everything
    digits.GrowMultiple(numdigits);
    for(nuint i = 0; i < numdigits; ++i)
        digits[i] = other.digits[i];

    return *this;
}

const CBigInt& CBigInt::operator=(nuint other) {
    digits.Clear();

    while(other > 0) {
        digits.Grow(uint8(other % 10));

        // -- check our digit limit
        if(limit > 0 && digits.Count() >= limit)
            break;

        other /= 10;
    }

    return *this;
}

// ================================================================================================
// Accumulate add
// ================================================================================================
const CBigInt& CBigInt::operator+=(const CBigInt& other) {
    // -- if we have less digits than the other number, pad out ours with zeros to the same size
    nuint othernum = other.NumDigits();

    // -- apply the digit limit, if necessary
    if(limit > 0 && othernum > limit)
        othernum = limit;

    nuint selfnum = NumDigits();
    if(othernum > selfnum)
        digits.GrowMultiple(0, othernum - selfnum);

    // -- handle all the digits that need to be added together
    uint8 carry = 0;
    nuint i = 0;
    for(; i < othernum; ++i) {
        digits[i] += carry + other.digits[i];
        carry = digits[i] / 10;
        digits[i] -= carry * 10;
    }

    // -- go through the rest of our digits until carry is zero
    for(; i < selfnum && carry != 0; ++i) {
        digits[i] += carry;
        carry = digits[i] / 10;
        digits[i] -= carry * 10;
    }

    // -- if we make it all the way through our digits and still have a carry value
    // -- just add one more digit for it
    if(carry != 0 && (limit == 0 || digits.Count() < limit))
        digits.Grow(carry);

    return *this;
}

// ================================================================================================
// Accumulate multiply
// ================================================================================================
const CBigInt& CBigInt::operator*=(nuint other) {
    // -- multiply each digit, starting with the most significant
    for(nuint i = digits.Count(); i > 0;) {
        --i;

        nuint product = digits[i] * other;
        digits[i] = 0;

        nuint j = i;
        uint8 carry = 0;
        while(product > 0) {
            if(j < digits.Count()) {
                digits[j] += uint8(product % 10);
                carry = digits[j] / 10;
                digits[j] -= carry * 10;
            }
            else if(limit == 0 || digits.Count() < limit)
                digits.Grow(uint8(product % 10));
            product = product / 10 + carry;
            carry = 0;
            ++j;
        }
    }

    return *this;
}

