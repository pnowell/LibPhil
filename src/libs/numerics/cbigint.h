#pragma once

// -- libs includes
#include "containers/ctable.h"
#include "core/types.h"

// ================================================================================================
// A class to handle arbitrary sized integers
// ================================================================================================
class CBigInt {

protected:

    CTable<uint8> digits;

public:

    CBigInt(nuint val = 0);
    CBigInt(cpointer v);

    // -- swap memory with the given big int
    void Swap(CBigInt& other);

    // -- accessors
    nuint NumDigits() const;
    nuint Digit(nuint idx) const;

    // -- operators
    const CBigInt& operator+=(const CBigInt& other);
    const CBigInt& operator*=(const nuint& other);
};

// ================================================================================================
// Accessors
// ================================================================================================
inline nuint CBigInt::NumDigits() const {
    return digits.Count();
}

inline nuint CBigInt::Digit(nuint idx) const {
    return digits[idx];
}

