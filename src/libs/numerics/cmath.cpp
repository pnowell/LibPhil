// -- system includes
#include <stdlib.h>

// -- libs includes
#include "numerics/cmath.h"

// ================================================================================================
// Stand in for the system atoi function
// ================================================================================================
sintn CMath::AToI(cpointer a) {
    return atoi(a);
}
