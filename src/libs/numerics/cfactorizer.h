#pragma once

// -- libs includes
#include "core/types.h"
#include "containers/ctable.h"

// -- forward declarations
class CPrimeCalculator;

// ================================================================================================
// Class with functionality for finding prime factors / divisors of integers
// ================================================================================================
class CFactorizer {

protected:

    // -- recursive function used when collecting divisors
    static void CollectFactorCombinations(const CTable<nuint>& factors, nuint curr, nuint prod,
                                          CTable<nuint>& divisors);

public:

    // -- find all the prime factors of the given number
    static void CollectFactors(nuint num, CPrimeCalculator& primecalc, CTable<nuint>& factors,
                               nflag cleartable = true);

    // -- make all the combinations of factors to build a table of divisors
    static void CollectDivisors(const CTable<nuint>& factors, CTable<nuint>& divisors);
};

