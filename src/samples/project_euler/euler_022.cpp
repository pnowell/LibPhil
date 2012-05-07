// -- libs includes
#include "core/types.h"
#include "core/assert.h"
#include "containers/ctable.h"
#include "containers/cstring.h"
#include "io/clog.h"

// -- constants
static const uintn kAnswer = 871198282;

// -- a list of names
static cpointer kNames[] = {
    #include "names.txt"
};
static const uintn kNameCount = ArraySize_(kNames);

// ================================================================================================
// Problem 22
// ================================================================================================
int32 Problem22() {
    CTable<cpointer> names;

    // -- first just fill the table of names
    for(uintn i = 0; i < kNameCount; ++i)
        names.Grow(kNames[i]);

    // -- then sort it using a compare function provided by CString
    names.Sort<CString>();

    uintn score = 0;
    uintn count = names.Count();
    for(uintn i = 0; i < count; ++i) {
        cpointer name = names[i];

        uintn curr = 0;
        for(uintn j = 0; name[j] != '\0'; ++j)
            curr += CString::ToUpper(name[j]) - 'A' + 1;
        score += curr * (i+1);
    }

    CLog::Write("Total name score is " UintNFmt_ "\n", score);
    Assert_(score == kAnswer, "The answer should have been " UintNFmt_, kAnswer);
    
    return 0;
}
