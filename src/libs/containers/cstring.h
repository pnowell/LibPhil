#pragma once

// -- libs includes
#include "containers/ctable.h"

// ================================================================================================
// A general string interface
// ================================================================================================
class CString {

protected:

    CTable<sint8> str;

public:

    // -- constructors
    CString();
    CString(cpointer s, ...);
    CString(const CString& other);

    // -- access the string as a cpointer (when empty, it returns a fixed empty string)
    cpointer GetString() const;

    // -- access to the string for direct modification, returns NULL if empty
    pointer ModifyString();

    // -- current length of the string
    uintn Length() const;

    // -- static utilities
    static sint8 ToLower(sint8 c);
    static sint8 ToUpper(sint8 c);
    static uintn Length(cpointer s);

    // -- static comparison of two strings
    static sintn Compare(const CString& left, const CString& right, flagn ignorecase = false);
    static sintn Compare(const CString* left, const CString* right, flagn ignorecase = false);
    static sintn Compare(cpointer left, cpointer right, flagn ignorecase = false);
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

inline uintn CString::Length() const {
    uintn result = 0;
    uintn count = str.Count();
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
inline sintn CString::Compare(const CString& left, const CString& right, flagn ignorecase) {
    return Compare(left.GetString(), right.GetString(), ignorecase);
}

inline sintn CString::Compare(const CString* left, const CString* right, flagn ignorecase) {
    return Compare(left->GetString(), right->GetString(), ignorecase);
}

