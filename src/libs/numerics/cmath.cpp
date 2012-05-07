// -- system includes
#include <stdlib.h>

// -- libs includes
#include "numerics/cmath.h"

// ================================================================================================
// Stand in for the system atoi function
// ================================================================================================
intn CMath::AToI(cpointer a) {
    return atoi(a);
}
