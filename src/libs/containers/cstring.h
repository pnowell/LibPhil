#pragma once

// -- libs includes
#include "containers/ctable.h"

// ================================================================================================
// A general string interface
// ================================================================================================
class CString {

protected:

    CTable<int8> str;

public:

    // -- constructors
    CString();
    CString(cpointer s);
    CString(cpointer s, ...);
    CString(const CString& other);

    // -- access the string as a cpointer (when empty, it returns a fixed empty string)
    cpointer GetString() const;

    // -- access to the string for direct modification, returns NULL if empty
    pointer ModifyString();

    // -- current length of the string
    nuint Length() const;

    // -- static utilities
    static int8 ToLower(int8 c);
    static int8 ToUpper(int8 c);
    static nuint Length(cpointer s);

    // -- static comparison of two strings
    static nint Compare(const CString& left, const CString& right, nflag ignorecase = false);
    static nint Compare(const CString* left, const CString* right, nflag ignorecase = false);
    static nint Compare(cpointer left, cpointer right, nflag ignorecase = false);
};

// ================================================================================================
// Constructor
// ================================================================================================
inline CString::CString() : str() {
}

// ================================================================================================
// Accessors
// ================================================================================================
inline cpointer CString::GetString() const {
    return str.Count() > 0 ? str.GetElem(0) : "";
}

inline pointer CString::ModifyString() {
    return str.Count() > 0 ? str.GetElem(0) : NULL;
}

inline nuint CString::Length() const {
    nuint result = 0;
    nuint count = str.Count();
    if(count == 0)
        return 0;
    cpointer s = str.GetElem(0);
    while(result < count && s[result] != '\0')
        ++result;
    return result;
}

// ================================================================================================
// Static comparison methods
// ================================================================================================
inline nint CString::Compare(const CString& left, const CString& right, nflag ignorecase) {
    return Compare(left.GetString(), right.GetString(), ignorecase);
}

inline nint CString::Compare(const CString* left, const CString* right, nflag ignorecase) {
    return Compare(left->GetString(), right->GetString(), ignorecase);
}

