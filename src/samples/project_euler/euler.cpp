// -- system includes
#include <stdio.h>
#include <stdlib.h>

// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "numerics/csieve.h"

// -- extern the current problem to run
typedef int32 (*ProblemCB)(void);
extern int32 Problem4();
extern int32 Problem7();
extern int32 Problem8();
extern int32 Problem9();
extern int32 Problem10();
extern int32 Problem11();
extern int32 Problem12();
extern int32 Problem13();
extern int32 Problem14();
extern int32 Problem15();
extern int32 Problem16();
extern int32 Problem17();
extern int32 Problem18();
extern int32 Problem19();
extern int32 Problem20();
extern int32 Problem21();
extern int32 Problem23();
extern int32 Problem24();
extern int32 Problem25();
extern int32 Problem26();
extern int32 Problem27();
extern int32 Problem28();
extern int32 Problem29();
extern int32 Problem48();
extern int32 Problem67();

static const ProblemCB kDefault = Problem29;

static const ProblemCB kProblems[] = {
    NULL,       NULL,       NULL,       Problem4,   NULL,       NULL,       Problem7,   Problem8,
    Problem9,   Problem10,  Problem11,  Problem12,  Problem13,  Problem14,  Problem15,  Problem16,
    Problem17,  Problem18,  Problem19,  Problem20,  Problem21,  NULL,       Problem23,  Problem24,
    Problem25,  Problem26,  Problem27,  Problem28,  Problem29,  NULL,       NULL,       NULL, // 32
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL, // 40
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       Problem48,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL, // 56
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL, // 64
    NULL,       NULL,       Problem67,
};
static const nuint kNumProblems = ArraySize_(kProblems);

// ================================================================================================
int32 main(int32 argc, pointer argv[]) {
    if(argc > 1) {
        nuint idx = atoi(argv[1]);

        // -- we use zero as a special index which means to iterate over all of the problems
        if(idx == 0) {
            for(nuint i = 0; i < kNumProblems; ++i) {
                if(kProblems[i] != NULL) {
                    printf("\n\n====================\n");
                    printf("Problem " NUintFmt_ "\n", i + 1);
                    printf("====================\n");
                    kProblems[i]();
                }
            }
        }
        else {
            --idx;
            if(idx >= kNumProblems || kProblems[idx] == NULL) {
                printf("Problem " NUintFmt_ " isn't solved yet\n", idx+1);
            }
            else
                kProblems[idx]();
        }
    }
    else
        kDefault();

    return 0;
}
