#pragma once

// -- types
typedef char* pointer;
typedef const pointer cpointer;
typedef void* vpointer;
typedef const vpointer cvpointer;

// -- integer types
typedef int nint;
typedef unsigned int nuint;
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef long long int64;
typedef unsigned long long uint64;

// -- boolean types
typedef bool nflag;

// -- floating point types
typedef float nreal;
typedef float real32;
typedef double real64;

// -- constants
#ifndef NULL
#define NULL 0
#endif
