#pragma once

// -- libs includes
#include "core/types.h"

// -- we only define asserts when in debug
#if Debug_
#define Assert_(cond, fmt, ...) \
    ((cond) ? (void)0 : AssertHandler(__FILE__, __LINE__, fmt , ##__VA_ARGS__))

// -- a globally scoped function for handling the failed assertions
void AssertHandler(cpointer file, nuint line, cpointer errorfmt, ...);

#else
#define Assert_(cond, fmt, ...) ((void)0)
#endif

