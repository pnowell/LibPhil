#pragma once

// -- types
typedef char* pointer;
typedef char const * cpointer;
typedef void* vpointer;
typedef void const * cvpointer;

// -- integer types
typedef char sint8;
typedef unsigned char uint8;
typedef short sint16;
typedef unsigned short uint16;
typedef long sint32;
typedef unsigned long uint32;
typedef long long sint64;
typedef unsigned long long uint64;
typedef uint64 uintp;
typedef sint64 sintp;

#define IntNFmt_ "%lld"
#define UintNFmt_ "%llu"
#define IntNIs32_ 0
#define IntNIs64_ 1

// -- natural int types
typedef sint64 sintn;
typedef uint64 uintn;

// -- system int types
typedef int sints;
typedef unsigned int uints;

// -- boolean types
typedef bool flagn;

// -- floating point types
typedef float real32;
typedef double real64;

// -- natural float type
typedef real32 realn;

#define RealNIs32_ 1
#define RealNIs64_ 0
#define RealNFmt_ "%lf"

// -- constants
#ifndef NULL
#define NULL 0
#endif

// -- maximum values for unsigned ints
const uint8 kNeverIndex8 = uint8(-1);
const uint16 kNeverIndex16 = uint16(-1);
const uint32 kNeverIndex32 = uint32(-1);
const uint64 kNeverIndex64 = uint64(-1);
const uintp kNeverIndexP = uintp(-1);
const uints kNeverIndexS = uints(-1);
const uintn kNeverIndexN = uintn(-1);
