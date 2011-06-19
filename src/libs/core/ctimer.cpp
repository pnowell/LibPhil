// -- system includes
#include <windows.h>
#include <time.h>

// -- libs includes
#include "core/ctimer.h"

enum {
    ePerfCounter,
    eClock,
};

// ================================================================================================
// Constructor
// ================================================================================================
CTimer::CTimer() : start(0), stop(0) {
    LARGE_INTEGER f;
    if(!QueryPerformanceFrequency(&f))
        f.QuadPart = 0;

    if(f.QuadPart > CLOCKS_PER_SEC) {
        mode = ePerfCounter;
        freq = f.QuadPart;
    }
    else {
        mode = eClock;
        freq = CLOCKS_PER_SEC;
    }
}

// ================================================================================================
// Start the timer
// ================================================================================================
void CTimer::Start() {
    switch(mode) {
        case ePerfCounter: {
            LARGE_INTEGER s;
            QueryPerformanceCounter(&s);
            start = s.QuadPart;
            break;
        }
        case eClock: {
            start = clock();
            break;
        }
    }
}

void CTimer::Stop() {
    switch(mode) {
        case ePerfCounter: {
            LARGE_INTEGER s;
            QueryPerformanceCounter(&s);
            stop = s.QuadPart;
            break;
        }
        case eClock: {
            stop = clock();
            break;
        }
    }
}

