#define MATHEVAL_IMPLEMENTATION

#include "../evaluator.hpp"
#include "ast.hpp"
#include "matheval.hpp"

#include <iostream>

namespace matheval {

namespace ast {

ConstantFolder::result_type ConstantFolder::operator()(nil) const {
    return result_type{0};
}

ConstantFolder::result_type ConstantFolder::operator()(double n) const {
    return result_type{n};
}

ConstantFolder::result_type ConstantFolder::
operator()(expression const &x) const {
    auto state = boost::apply_visitor(*this, x.lhs);
    for (operation const &oper : x.rhs) {
        state = (*this)(oper, state);
    }
    return result_type{state};
}

// Evaluator

double eval::operator()(nil) const {
    throw matheval::invalid_argument("operator nil called");
    BOOST_ASSERT(0);
    return 0;
}

double eval::operator()(double n) const { return n; }

double eval::operator()(std::string const &var) const {
  if (! fn) {
    throw matheval::invalid_argument("Missing callback function to look up variable " + var); // NOLINT
  }
  return fn(var);
}

double eval::operator()(operation const &x, double lhs) const {
    double rhs = boost::apply_visitor(*this, x.rhs);
    return x.op(lhs, rhs);
}

double eval::operator()(unary_op const &x) const {
    double rhs = boost::apply_visitor(*this, x.rhs);
    return x.op(rhs);
}

double eval::operator()(binary_op const &x) const {
    double lhs = boost::apply_visitor(*this, x.lhs);
    double rhs = boost::apply_visitor(*this, x.rhs);
    return x.op(lhs, rhs);
}

double eval::operator()(ternary_op const &x) const {
    double p1 = boost::apply_visitor(*this, x.p1);
    double p2 = boost::apply_visitor(*this, x.p2);
    double p3 = boost::apply_visitor(*this, x.p3);
    return x.op(p1, p2, p3);
}

double eval::operator()(expression const &x) const {
    double state = boost::apply_visitor(*this, x.lhs);
    for (operation const &oper : x.rhs) {
        state = (*this)(oper, state);
    }
    return state;
}

} // namespace ast

} // namespace matheval
