// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "core/assert.h"
#include "io/clog.h"

// -- constants
static const int32 kAnswer = 31875000;

// ================================================================================================
// Find the triplet of numbers such that a^2 + b^2 = c^2 and a+b+c = 1000
// ================================================================================================
int32 Problem9() {
    int32 a = 1;
    int32 b = 2;
    int32 c = 0;
    
    while(b < 1000) {
        c = 1000 - a - b;
        if(c < b) {
            ++a;
            b = a + 1;

            continue;
        }

        if(a*a + b*b == c*c)
            break;

        ++b;
    }

    // -- make sure we got the right answer
    Assert_(b <= 1000, "The loop ended without finding the answer");
    Assert_(a*b*c == kAnswer, "The answer is incorrect");

    CLog::Write("%ld^2 + %ld^2 = %ld^2\n", a, b, c);
    CLog::Write("and %ld * %ld * %ld = %ld\n", a, b, c, a*b*c);

    return 0;
}
