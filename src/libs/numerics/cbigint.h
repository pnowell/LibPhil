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
    uintn limit;

public:

    CBigInt(uintn val = 0);
    CBigInt(cpointer v);

    // -- limit the number of digits
    void SetDigitLimit(uintn lim);
    void ClearDigitLimit();

    // -- swap memory with the given big int
    void Swap(CBigInt& other);

    // -- accessors
    uintn NumDigits() const;
    uintn Digit(uintn idx) const;

    // -- operators
    const CBigInt& operator=(const CBigInt& other);
    const CBigInt& operator=(uintn other);
    const CBigInt& operator+=(const CBigInt& other);
    const CBigInt& operator*=(uintn other);
};

// ================================================================================================
// Accessors
// ================================================================================================
inline uintn CBigInt::NumDigits() const {
    return digits.Count();
}

inline uintn CBigInt::Digit(uintn idx) const {
    return digits[idx];
}

