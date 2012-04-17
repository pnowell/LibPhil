#pragma once

// -- forward declarations
class CPrimeCalculator;

// -- we want to use one prime calculator for all the problems (rather than recomputing
// -- primes over and over)
CPrimeCalculator& PrimeCalculator();
