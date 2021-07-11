#define BOOST_TEST_MODULE arithmetic
#include "exprtest.hpp"

EXPRTEST(basicop1, " 2 +\t3\n",  5)       // Whitespace ignored
EXPRTEST(basicop2, " 2 -\t3\n", -1)
EXPRTEST(basicop3, " 2 *\t3\n",  6)
EXPRTEST(basicop4, " 2 /\t3\n",  2./3.)   // Double division
EXPRTEST(basicop5, " 2 ** 3\n",  8)
EXPRTEST(basicop6, "10 % 5",  0)
EXPRTEST(basicop7, "11 % 5",  1)

THROWTEST(divideByZero1, "1/0", matheval::divideByZero)
THROWTEST(divideByZero2, "3/0", matheval::exception)
THROWTEST(divideByZero3, "5/(-3+2+1)", std::exception)
THROWTEST(moduloByZero1, "10 % 0", std::exception)
THROWTEST(moduloByZero2, "10 % 0", matheval::exception)
THROWTEST(moduloByZero3, "10 % 0", matheval::moduloByZero)

EXPRTEST(isinf1, "isinf(inf) > 0",  1)
THROWTEST(moduloWithInfinity, "inf % 3", matheval::moduloWithInfinity)
