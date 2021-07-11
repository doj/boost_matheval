#define BOOST_TEST_MODULE errors
#include "exprtest.hpp"

THROWTEST(parse_failure, "#", matheval::parse_error)
THROWTEST(expectation_failure, "(", matheval::parse_error)
THROWTEST(unknown_variable, "x", matheval::invalid_argument)
