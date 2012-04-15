// -- system includes
#include <stdarg.h>
#include <stdio.h>

// -- libs includes
#include "containers/cstring.h"

// ================================================================================================
// Constructors
// ================================================================================================
CString::CString(cpointer s) {
    nuint len = CString::Length(s);
    str.GrowMultiple(len + 1);
    pointer p = str.GetElem(0);
    for(nuint i = 0; i < len; ++i)
        p[i] = s[i];
    p[len] = '\0';
}

CString::CString(cpointer s, ...) {
    va_list args;
    va_start(args, s);
    nuint len = _vscprintf(s, args);
    str.Clear();
    str.GrowMultiple('\0', len + 1); 
    vsnprintf_s(str.GetElem(0), len + 1, len, s, args);
    va_end(args);
}

CString::CString(const CString& other) {
    nuint len = other.Length();
    str.GrowMultiple(len + 1);
    pointer p = str.GetElem(0);
    cpointer s = other.GetString();
    for(nuint i = 0; i < len; ++i)
        p[i] = s[i];
    p[len] = '\0';
}

// ================================================================================================
// Static utilities for frequently used string / character operations
// ================================================================================================
int8 CString::ToLower(int8 c) {
    if('A' <= c && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

int8 CString::ToUpper(int8 c) {
    if('a' <= c && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

nuint CString::Length(cpointer s) {
    nuint result = 0;
    while(s[result] != '\0')
        ++result;
    return result;
}

// ================================================================================================
// Comparison of two strings
// ================================================================================================
nint CString::Compare(cpointer left, cpointer right, nflag ignorecase) {
    nuint i = 0;
    while(left[i] != 0 && right[i] != 0) {
        if(ignorecase) {
            int8 l = ToLower(left[i]);
            int8 r = ToLower(right[i]);
            if(l != r)
                return l - r;
        }
        else {
            if(left[i] != right[i])
                return left[i] - right[i];
        }
        ++i;
    }
    if(right[i] != 0)
        return -1;
    if(left[i] != 0)
        return 1;
    return 0;
}

