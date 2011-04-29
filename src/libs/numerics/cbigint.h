#pragma once

// -- libs includes
#include "containers/ctable.h"
#include "core/types.h"

// ================================================================================================
// A class to handle arbitrary sized integers
// ================================================================================================
class CBigInt {

protected:

    nflag negative;
    CTable<uint8> digits;
    nuint numdigits;

public:

    CBigInt(int64 v = 0);
    CBigInt(cpointer v);

    // -- accessors
    nuint NumDigits();
    nuint Digit(nuint idx);

    // -- operators
    CBigInt& operator+=(const CBigInt& other);
    CBigInt& operator-=(const CBigInt& other);
    CBigInt& operator*=(const CBigInt& other);
};

// ================================================================================================
// Accessors
// ================================================================================================
inline nuint CBigInt::NumDigits() {
    return digits.Count();
}

inline nuint CBigInt::Digit(nuint idx) {
    return digits[idx];
}

