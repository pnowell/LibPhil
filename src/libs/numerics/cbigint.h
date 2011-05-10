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
    nuint limit;

public:

    CBigInt(nuint val = 0);
    CBigInt(cpointer v);

    // -- limit the number of digits
    void SetDigitLimit(nuint lim);
    void ClearDigitLimit();

    // -- swap memory with the given big int
    void Swap(CBigInt& other);

    // -- accessors
    nuint NumDigits() const;
    nuint Digit(nuint idx) const;

    // -- operators
    const CBigInt& operator=(const CBigInt& other);
    const CBigInt& operator=(nuint other);
    const CBigInt& operator+=(const CBigInt& other);
    const CBigInt& operator*=(nuint other);
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

