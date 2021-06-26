#ifndef MATHEVAL_IMPLEMENTATION
#error "Do not include ast.hpp directly!"
#endif

#pragma once

#include <boost/variant.hpp>

#include <list>
#include <string>

namespace matheval {

namespace ast {

struct nil {};
struct unary_op;
struct binary_op;
struct ternary_op;
struct expression;

// clang-format off
typedef boost::variant<
        nil // can't happen!
        , double
        , std::string
        , boost::recursive_wrapper<unary_op>
        , boost::recursive_wrapper<binary_op>
        , boost::recursive_wrapper<ternary_op>
        , boost::recursive_wrapper<expression>
        >
operand;
// clang-format on

struct unary_op {
    double (*op)(double);
    operand rhs;
    unary_op() {}
    unary_op(double (*op)(double), operand const &rhs) : op(op), rhs(rhs) {}
};

struct binary_op {
    double (*op)(double, double);
    operand lhs;
    operand rhs;
    binary_op() {}
    binary_op(double (*op)(double, double), operand const &lhs,
              operand const &rhs)
        : op(op), lhs(lhs), rhs(rhs) {}
};

struct ternary_op {
    double (*op)(double, double, double);
    operand p1, p2, p3;
    ternary_op() {}
    ternary_op(double (*op_)(double, double, double),
	       operand const &p1_,
               operand const &p2_,
	       operand const &p3_)
      : op(op_), p1(p1_), p2(p2_), p3(p3_) {}
};

struct operation {
    double (*op)(double, double);
    operand rhs;
    operation() {}
    operation(double (*op)(double, double), operand const &rhs)
        : op(op), rhs(rhs) {}
};

struct expression {
    operand lhs;
    std::list<operation> rhs;
    expression() {}
    expression(operand const &lhs, std::list<operation> const &rhs)
        : lhs(lhs), rhs(rhs) {}
};

} // namespace ast

} // namespace matheval
