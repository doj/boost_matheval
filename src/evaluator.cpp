#define MATHEVAL_IMPLEMENTATION

#include "../evaluator.hpp"
#include "ast.hpp"

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
    BOOST_ASSERT(0);
    return 0;
}

double eval::operator()(double n) const { return n; }

double eval::operator()(std::string const &var) const {
  if (! fn) {
    throw std::invalid_argument("Missing symbol table to look up variable " + var); // NOLINT
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

double eval::operator()(expression const &x) const {
    double state = boost::apply_visitor(*this, x.lhs);
    for (operation const &oper : x.rhs) {
        state = (*this)(oper, state);
    }
    return state;
}

} // namespace ast

} // namespace matheval
