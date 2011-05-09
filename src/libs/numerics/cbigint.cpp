// -- libs includes
#include "numerics/cbigint.h"

// ================================================================================================
// Constructors
// ================================================================================================
CBigInt::CBigInt(nuint val) {
    while(val > 0) {
        digits.Grow(uint8(val % 10));
        val /= 10;
    }
}

CBigInt::CBigInt(cpointer v) {
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
// Accumulate add
// ================================================================================================
const CBigInt& CBigInt::operator+=(const CBigInt& other) {
    // -- if we have less digits than the other number, pad out ours with zeros to the same size
    nuint othernum = other.NumDigits();
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
    if(carry != 0)
        digits.Grow(carry);

    return *this;
}

// ================================================================================================
// Accumulate multiply
// ================================================================================================
const CBigInt& CBigInt::operator*=(const nuint& other) {
    // -- multiply each digit, starting with the most significant
    for(nuint i = digits.Count(); i > 0;) {
        --i;

        nuint product = digits[i] * other;
        digits[i] = 0;

        nuint j = i;
        while(product > 0) {
            if(j < digits.Count())
                digits[j] += uint8(product % 10);
            else
                digits.Grow(uint8(product % 10));
            product /= 10;
            ++j;
        }
    }

    return *this;
}

