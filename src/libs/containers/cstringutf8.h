#pragma once

// -- libs includes
#include "containers/ctable.h"

// ================================================================================================
// A general string interface
// ================================================================================================
class CStringUTF8 {

protected:

    CTable<uint8> str;
    uintn len;
    flagn valid;

    // -- reset the string part of our representation
    void ResetString();

public:

    // -- constructors
    CStringUTF8();
    CStringUTF8(cpointer s);

    // -- access the string as a cpointer (when empty, it returns a fixed empty string)
    cpointer GetString() const;

    // -- number of characters in the string (not including null terminator)
    uintn Length() const;

    // -- size of the string in bytes (including null terminator)
    uintn Size() const;

    // -- is this string valid (was it invalidated by invalid input)
    flagn Valid() const;

    // -- reset the string (clear it and make it valid again)
    void Reset();

    // -- append a single unicode character
    void Append(uint32 c);

    // -- get the next character (and increment the iterator)
    // -- if the string changes between calls to this function, the next call might
    // -- continue to report characters from some place in the string, or may suddenly terminate
    // -- iteration (returning 0 and invalidating the iterator)
    uint32 GetNextChar(uintn& iter) const;

    // -- append another utf8 string
    void Append(const CStringUTF8& s);
};

// ------------------------------------------------------------------------------------------------
// Reset the string storage
// ------------------------------------------------------------------------------------------------
inline void CStringUTF8::ResetString() {
    str.Clear();
    len = 0;
}

// ================================================================================================
// Constructor
// ================================================================================================
inline CStringUTF8::CStringUTF8() : str(), len(0), valid(true) {
}

// ================================================================================================
// Accessors
// ================================================================================================
inline cpointer CStringUTF8::GetString() const {
    return str.Count() > 0 ? cpointer(str.GetElem(0)) : "";
}

// ================================================================================================
// Get the length in characters
// ================================================================================================
inline uintn CStringUTF8::Length() const {
    return len;
}

// ================================================================================================
// Get the size in bytes including the terminating null character
// ================================================================================================
inline uintn CStringUTF8::Size() const {
    return str.Count();
}

// ================================================================================================
// Is this string valid
// ================================================================================================
inline flagn CStringUTF8::Valid() const {
    return valid;
}

// ================================================================================================
// Reset the string (clear it's contents and make it valid again)
// ================================================================================================
inline void CStringUTF8::Reset() {
    ResetString();
    valid = true;
}
