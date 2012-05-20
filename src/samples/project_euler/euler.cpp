// -- libs includes
#include "core/types.h"
#include "core/utils.h"
#include "core/ctimer.h"
#include "numerics/cmath.h"
#include "numerics/cprimecalculator.h"
#include "io/clog.h"

// -- local includes
#include "euler.h"

// -- extern the current problem to run
typedef sint32 (*ProblemCB)(void);
extern sint32 Problem4();
extern sint32 Problem7();
extern sint32 Problem8();
extern sint32 Problem9();
extern sint32 Problem10();
extern sint32 Problem11();
extern sint32 Problem12();
extern sint32 Problem13();
extern sint32 Problem14();
extern sint32 Problem15();
extern sint32 Problem16();
extern sint32 Problem17();
extern sint32 Problem18();
extern sint32 Problem19();
extern sint32 Problem20();
extern sint32 Problem21();
extern sint32 Problem22();
extern sint32 Problem23();
extern sint32 Problem24();
extern sint32 Problem25();
extern sint32 Problem26();
extern sint32 Problem27();
extern sint32 Problem28();
extern sint32 Problem29();
extern sint32 Problem30();
extern sint32 Problem31();
extern sint32 Problem32();
extern sint32 Problem33();
extern sint32 Problem34();
extern sint32 Problem35();
extern sint32 Problem36();
extern sint32 Problem48();
extern sint32 Problem67();

static const ProblemCB kDefault = Problem36;

static const ProblemCB kProblems[] = {
    NULL,       NULL,       NULL,       Problem4,   NULL,       NULL,       Problem7,   Problem8,
    Problem9,   Problem10,  Problem11,  Problem12,  Problem13,  Problem14,  Problem15,  Problem16,
    Problem17,  Problem18,  Problem19,  Problem20,  Problem21,  Problem22,  Problem23,  Problem24,
    Problem25,  Problem26,  Problem27,  Problem28,  Problem29,  Problem30,  Problem31,  Problem32,
    Problem33,  Problem34,  Problem35,  Problem36,  NULL,       NULL,       NULL,       NULL, // 40
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       Problem48,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL, // 56
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL, // 64
    NULL,       NULL,       Problem67,
};
static const uintn kNumProblems = ArraySize_(kProblems);

// ================================================================================================
// One common prime calculator to share amongst the various problems
// ================================================================================================
static CPrimeCalculator primecalc;
CPrimeCalculator& PrimeCalculator() {
    return primecalc;
}

// ================================================================================================
// Time the call to a particular function
// ================================================================================================
static void TimeCall(ProblemCB cb) {
    // -- time the execution of each solution
    CTimer timer;

    timer.Start();
    cb();
    timer.Stop();

    // -- print the number of seconds / milliseconds it took to run
    CLog::Write(" -- %.5f secs (" UintNFmt_ " usecs)\n", timer.GetSeconds(), timer.GetMicro());
}

// ================================================================================================
// Entry point
// ================================================================================================
int main(sint32 argc, pointer argv[]) {
    CTimer timer;
    timer.Start();

    if(argc > 1) {
        uintn idx = CMath::AToI(argv[1]);

        // -- we use zero as a special index which means to iterate over all of the problems
        if(idx == 0) {
            for(uintn i = 0; i < kNumProblems; ++i) {
                if(kProblems[i] != NULL) {
                    CLog::Write("\n\n====================\n");
                    CLog::Write("Problem " UintNFmt_ "\n", i + 1);
                    CLog::Write("====================\n");
                    TimeCall(kProblems[i]);
                }
            }
        }
        else {
            --idx;
            if(idx >= kNumProblems || kProblems[idx] == NULL) {
                CLog::Write("Problem " UintNFmt_ " isn't solved yet\n", idx+1);
            }
            else
                TimeCall(kProblems[idx]);
        }
    }
    else
        TimeCall(kDefault);

    timer.Stop();
    CLog::Write(" ---- Total time %.5f secs (" UintNFmt_ " usecs)\n",
           timer.GetSeconds(), timer.GetMicro());

    return 0;
}
