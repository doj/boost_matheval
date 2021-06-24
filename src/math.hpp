#ifndef MATHEVAL_IMPLEMENTATION
#error "Do not include math.hpp directly!"
#endif

#pragma once

#include <boost/math/constants/constants.hpp>
#include <cmath>
#include "matheval.hpp"

namespace matheval {

namespace math {

/// @brief Sign function
template <typename T>
T sgn(T x) {
    return (T{0} < x) - (x < T{0});
}

/// @brief isnan function with adjusted return type
template <typename T>
T isnan(T x) {
    return std::isnan(x);
}

/// @brief isinf function with adjusted return type
template <typename T>
T isinf(T x) {
    return std::isinf(x);
}

/// @brief Convert radians to degrees
template <typename T>
T deg(T x) {
    return x * boost::math::constants::radian<T>();
}

/// @brief Convert degrees to radians
template <typename T>
T rad(T x) {
    return x * boost::math::constants::degree<T>();
}

/// @brief unary plus
template <typename T>
T plus(T x) {
    return x;
}

/// @brief binary plus
template <typename T>
T plus(T x, T y) {
    return x + y;
}

/// @brief unary minus
template <typename T>
T minus(T x) {
    return -x;
}

/// @brief binary minus
template <typename T>
T minus(T x, T y) {
    return x - y;
}

/// @brief multiply
template <typename T>
T multiplies(T x, T y) {
    return x * y;
}

/// @brief divide
template <typename T>
T divides(T x, T y) {
  if (y == 0) {
    throw matheval::divideByZero{};
  }
    return x / y;
}

/// @brief modulo
template <typename T>
T fmod(T x, T y) {
  if (y == 0) {
    throw matheval::moduloByZero{};
  }
  if (isinf(x)) {
    throw matheval::moduloWithInfinity{};
  }
  return std::fmod(x,y);
}

/// @brief power
template <typename T>
T pow(T x, T y) {
#if defined(__linux__)
  errno = 0;
  feclearexcept(FE_ALL_EXCEPT);
  T res = std::pow(x,y);
  if (fetestexcept(FE_INVALID)) {
    throw matheval::powInvalid{};
  } else if (fetestexcept(FE_DIVBYZERO)) {
    throw matheval::powDivideByZero{};
  } else if (fetestexcept(FE_OVERFLOW)) {
    throw matheval::powOverflow{};
  } else if (fetestexcept(FE_UNDERFLOW)) {
    throw matheval::powUnderflow{};
  }
  return res;
#elif defined(__APPLE__) && defined(__clang__)
  if (y < 0) {
    throw matheval::powDivideByZero{};
  } else if (x < 0 &&
	     isfinite(y) &&
	     y != floor(y)) {
    throw matheval::powInvalid{};
  } else if (x == 0 && y <= 0) {
    throw matheval::powInvalid{};
  }
  return std::pow(x,y);
#else
#error unknown platform
#endif
}

/// @brief unary not
template <typename T>
T unary_not(T x) {
    return !x;
}

/// @brief logical and
template <typename T>
T logical_and(T x, T y) {
    return x && y;
}

/// @brief logical or
template <typename T>
T logical_or(T x, T y) {
    return x || y;
}

/// @brief less
template <typename T>
T less(T x, T y) {
    return x < y;
}

/// @brief less equals
template <typename T>
T less_equals(T x, T y) {
    return x <= y;
}

/// @brief greater
template <typename T>
T greater(T x, T y) {
    return x > y;
}

/// @brief greater equals
template <typename T>
T greater_equals(T x, T y) {
    return x >= y;
}

/// @brief equals
template <typename T>
T equals(T x, T y) {
    return x == y;
}

/// @brief not equals
template <typename T>
T not_equals(T x, T y) {
    return x != y;
}

} // namespace math

} // namespace matheval
