#define BOOST_TEST_MODULE functions
#include <boost/test/included/unit_test.hpp>
#include "exprtest.hpp"

using boost::math::constants::pi;

EXPRTEST(func_abs   , "abs   (-1.1)", std::fabs  (-1.1))

EXPRTEST(func_acos  , "acos  ( 1.0)", std::acos  ( 1.0))
THROWTEST(acos1, "acos(1.1)", matheval::acosInvalid)
THROWTEST(acos2, "acos(-1.1)", matheval::acosInvalid)

EXPRTEST(func_acosh, "acosh(3.0)", std::acosh(3.0))
THROWTEST(acosh1, "acosh(-0.9)", matheval::acoshInvalid)

EXPRTEST(func_asin  , "asin  ( 1.0)", std::asin  ( 1.0))
THROWTEST(asin1, "asin(1.1)", matheval::asinInvalid)
THROWTEST(asin2, "asin(-1.1)", matheval::asinInvalid)

EXPRTEST(func_atan  , "atan  ( 1.0)", std::atan  ( 1.0))

EXPRTEST(func_atanh , "atanh ( 0.0)", std::atanh ( 0.0))
THROWTEST(atanh1, "atanh(+1.0)", matheval::atanhDivideByZero)
THROWTEST(atanh2, "atanh(-1.0)", matheval::divideByZero)
THROWTEST(atanh3, "atanh(+1.1)", matheval::atanhInvalid)
THROWTEST(atanh4, "atanh(-1.1)", matheval::atanhInvalid)

EXPRTEST(func_ceil  , "ceil  ( 0.5)", std::ceil  ( 0.5))
EXPRTEST(func_cos   , "cos   ( 1.0)", std::cos   ( 1.0))
EXPRTEST(func_cosh  , "cosh  ( 1.0)", std::cosh  ( 1.0))
EXPRTEST(func_deg   , "deg   (  pi)",              180 )
EXPRTEST(func_exp   , "exp   ( 1.0)", std::exp   ( 1.0))
EXPRTEST(func_floor , "floor ( 0.5)", std::floor ( 0.5))
EXPRTEST(func_isnan , "isnan ( nan)",                1 )
EXPRTEST(func_isinf , "isinf ( inf)",                1 )
EXPRTEST(func_log   , "log   ( 1.0)", std::log   ( 1.0))
EXPRTEST(func_log10 , "log10 ( 1.0)", std::log10 ( 1.0))
EXPRTEST(func_rad   , "rad   ( 180)",      pi<double>())
EXPRTEST(func_sgn   , "sgn   (-1.0)",             -1.0 )
EXPRTEST(func_sin   , "sin   ( 1.0)", std::sin   ( 1.0))
EXPRTEST(func_sinh  , "sinh  ( 1.0)", std::sinh  ( 1.0))
EXPRTEST(func_sqrt  , "sqrt  ( 1.0)", std::sqrt  ( 1.0))
EXPRTEST(func_tan   , "tan   ( 1.0)", std::tan   ( 1.0))
EXPRTEST(func_tanh  , "tanh  ( 1.0)", std::tanh  ( 1.0))

EXPRTEST(func_atan2, "atan2(2.0, 3.0)", std::atan2(2.0,3.0))

EXPRTEST(func_pow,   "pow  (2.0, 3.0)", std::pow(2.0,3.0))
#if __linux__
THROWTEST(pow1, "pow(-2, 2)", matheval::powInvalid)
THROWTEST(pow2, "pow(0, -3)", matheval::powDivideByZero)
THROWTEST(pow3, "pow(0, -3.14)", matheval::divideByZero)
#endif
#if __apple__
THROWTEST(pow1, "pow(-2, 2)", matheval::exception)
THROWTEST(pow2, "pow(0, -3)", matheval::exception)
THROWTEST(pow3, "pow(0, -3.14)", matheval::exception)
#endif
THROWTEST(pow4, "pow(-3, 3.14)", matheval::exception)
THROWTEST(pow5, "pow(0, 0)", matheval::exception)

#if __cplusplus >= 201402L
EXPRTEST(func_asinh , "asinh ( 1.0)", std::asinh ( 1.0))
EXPRTEST(func_cbrt  , "cbrt  ( 1.0)", std::cbrt  ( 1.0))
EXPRTEST(func_erf   , "erf   ( 1.0)", std::erf   ( 1.0))
EXPRTEST(func_erfc  , "erfc  ( 1.0)", std::erfc  ( 1.0))
EXPRTEST(func_exp2  , "exp2  ( 1.0)", std::exp2  ( 1.0))
EXPRTEST(func_log2  , "log2  ( 1.0)", std::log2  ( 1.0))
EXPRTEST(func_round , "round ( 0.5)", std::round ( 0.5))
EXPRTEST(func_tgamma, "tgamma( 4.0)", std::tgamma( 4.0))

EXPRTEST(func_max,   "max  (2.0, 3.0)", std::fmax(2.0,3.0))
EXPRTEST(func_min,   "min  (2.0, 3.0)", std::fmin(2.0,3.0))
#endif
