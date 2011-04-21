// -- system includes
#include <stdio.h>

// -- libs includes
#include "core/types.h"
#include "core/utils.h"

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

    if(b > 1000)
        printf("WTF\n");
    else {
        printf("%d^2 + %d^2 = %d^2\n", a, b, c);
        printf("and %d * %d * %d = %d\n", a, b, c, a*b*c);
    }

    return 0;
}
