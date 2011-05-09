#pragma once

// -- types
typedef char* pointer;
typedef char const * cpointer;
typedef void* vpointer;
typedef void const * cvpointer;

// -- integer types
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef long long int64;
typedef unsigned long long uint64;

#define NIntFmt_ "%lld"
#define NUintFmt_ "%llu"

// -- natural int types
typedef int64 nint;
typedef uint64 nuint;

// -- boolean types
typedef bool nflag;

// -- floating point types
typedef float real32;
typedef double real64;

// -- natural float type
typedef real32 nreal;

// -- constants
#ifndef NULL
#define NULL 0
#endif
