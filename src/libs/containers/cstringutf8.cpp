// -- libs includes
#include "containers/cstringutf8.h"

#define IsContinue_(c) (((c) & 0xc0) == 0x80)

// ================================================================================================
// Constructor from a const string (assumes the string is also UTF-8, but may be malformed)
// ================================================================================================
CStringUTF8::CStringUTF8(cpointer s) : str(), len(0), valid(true) {
    if(IsContinue_(*s)) {
        valid = false;
        return;
    }

    // -- first compute the length, and check if the input string is valid
    uintn slen = 0;
    sintn bytesleft = 0;
    uintn idx;
    for(idx = 0; s[idx] != 0; ++idx) {
        uint8 c = uint8(s[idx]);
        if(IsContinue_(c)) {
            --bytesleft;
            continue;
        }

        // -- if we expected more continue bytes, the input is invalid
        if(bytesleft != 0) {
            valid = false;
            return;
        }

        // -- count how many bytes this character should occupy
        while((c & 0x80) != 0) {
            c = c << 1;
            ++bytesleft;
        }

        // -- if we expected too many, the input is invalid
        if(bytesleft >= 6) {
            valid = false;
            return;
        }

        // -- this byte counts as the first byte (there were no high bits if it's a 1 byte char)
        if(bytesleft > 0)
            --bytesleft;

        // -- this is one more character
        ++slen;
    }

    // -- we shouldn't have left that loop still expecting more continue bytes
    if(bytesleft > 0) {
        valid = false;
        return;
    }

    // -- if we've made it this far, we just need to copy the data
    ++idx;
    str.GrowMultiple(idx);
    CMemory::Copy(str.GetElem(0), s, idx);
    len = slen;
}

// ================================================================================================
// Append a single unicode character
// ================================================================================================
void CStringUTF8::Append(uint32 c) {
    // -- 1 byte
    if(c <= 0x7fu)
        str.Grow(uint8(c));

    // -- 2 bytes
    else if(c <= 0x000007ffu) {
        uintn i = str.Count();
        str.GrowMultiple(2);
        str[i] = 0xc0 | uint8(c >> 6);
        str[i+1] = 0x80 | uint8(c & 0x3f);
    }

    // -- 3 bytes
    else if(c <= 0x0000ffffu) {
        uintn i = str.Count();
        str.GrowMultiple(3);
        str[i] = 0xe0 | uint8(c >> 12);
        str[i+1] = 0x80 | uint8((c >> 6) & 0x3f);
        str[i+2] = 0x80 | uint8(c & 0x3f);
    }

    // -- 4 bytes
    else if(c <= 0x001fffffu) {
        uintn i = str.Count();
        str.GrowMultiple(3);
        str[i] = 0xf0 | uint8(c >> 18);
        str[i+1] = 0x80 | uint8((c >> 12) & 0x3f);
        str[i+2] = 0x80 | uint8((c >> 6) & 0x3f);
        str[i+3] = 0x80 | uint8(c & 0x3f);
    }

    // -- 5 bytes
    else if(c <= 0x03ffffffu) {
        uintn i = str.Count();
        str.GrowMultiple(3);
        str[i] = 0xf8 | uint8(c >> 24);
        str[i+1] = 0x80 | uint8((c >> 18) & 0x3f);
        str[i+2] = 0x80 | uint8((c >> 12) & 0x3f);
        str[i+3] = 0x80 | uint8((c >> 6) & 0x3f);
        str[i+4] = 0x80 | uint8(c & 0x3f);
    }

    // -- 6 bytes
    else if(c <= 0x7fffffffu) {
        uintn i = str.Count();
        str.GrowMultiple(3);
        str[i] = 0xfc | uint8(c >> 30);
        str[i+1] = 0x80 | uint8((c >> 24) & 0x3f);
        str[i+2] = 0x80 | uint8((c >> 18) & 0x3f);
        str[i+3] = 0x80 | uint8((c >> 12) & 0x3f);
        str[i+4] = 0x80 | uint8((c >> 6) & 0x3f);
        str[i+5] = 0x80 | uint8(c & 0x3f);
    }

    // -- invalid
    else {
        Assert_(0, "Character 0x%08x too large to be encoded in UTF-8", c);
        return;
    }

    ++len;
}

// ================================================================================================
// Get the next character (and increment the iterator)
// ================================================================================================
uint32 CStringUTF8::GetNextChar(uintn& iter) const {
    if(iter > str.Count()) {
        iter = kNeverIndexN;
        return 0;
    }

    uint8 head = str[iter];
    if(IsContinue_(head)) {
        iter = kNeverIndexN;
        return 0;
    }

    // -- handle the 1 byte case
    if((head & 0x80) == 0) {
        ++iter;
        return head;
    }

    // -- iterate over the remaining bytes of this character
    uint8 mask = 0x40;
    uint8 shift = 0;
    uintn curr = 1;
    uint32 result = 0;
    while((head & mask) != 0) {
        uint8 c = str[iter + curr];
        result = (result << shift) | (c & 0x3f);

        mask = mask >> 1;
        shift += 6;
        ++curr;
    }

    // -- now we know how much of the head byte to copy
    result |= uint32((0xFFu >> curr) & head) << shift;

    // -- update the iterator
    iter += curr;

    // -- and return the result
    return result;
}

// ================================================================================================
// Append another UTF-8 string
// ================================================================================================
void CStringUTF8::Append(const CStringUTF8& s) {
    if(!s.valid) {
        ResetString();
        valid = false;
        return;
    }
    
    if(s.Size() == 0)
        return;

    uintn count = s.Size();
    uintn start = str.Count();

    // -- make room for the new characters
    str.GrowMultiple(count);

    // -- copy them
    CMemory::Copy(str.GetElem(start), s.str.GetElem(0), count);

    // -- increase our length
    len += s.len;
}

