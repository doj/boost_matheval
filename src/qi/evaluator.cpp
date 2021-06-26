#define MATHEVAL_IMPLEMENTATION

#include "../evaluator.hpp"
#include "ast.hpp"

namespace matheval {

namespace ast {

// Optimizer

template <typename T, typename U>
struct is_same {
    static const bool value = false;
};

template <typename T>
struct is_same<T, T> {
    static const bool value = true;
};

template <typename T>
struct holds_alternative_impl {
    typedef bool result_type;

    template <typename U>
    bool operator()(U const & /*unused*/) const {
        return is_same<U, T>::value;
    }
};

template <typename T>
bool holds_alternative(operand const &v) {
    return boost::apply_visitor(holds_alternative_impl<T>(), v);
}

ConstantFolder::result_type ConstantFolder::
operator()(std::string const &c) const {
    return c;
}

ConstantFolder::result_type ConstantFolder::
operator()(operation const &x, operand const &lhs) const {
    operand rhs = boost::apply_visitor(*this, x.rhs);

    if (holds_alternative<double>(lhs) && holds_alternative<double>(rhs)) {
        return x.op(boost::get<double>(lhs), boost::get<double>(rhs));
    }
    return binary_op(x.op, lhs, rhs);
}

ConstantFolder::result_type ConstantFolder::
operator()(unary_op const &x) const {
    operand rhs = boost::apply_visitor(*this, x.rhs);

    /// If the operand is known, we can directly evaluate the function.
    if (holds_alternative<double>(rhs)) {
        return x.op(boost::get<double>(rhs));
    }
    return unary_op(x.op, rhs);
}

ConstantFolder::result_type ConstantFolder::
operator()(binary_op const &x) const {
    operand lhs = boost::apply_visitor(*this, x.lhs);
    operand rhs = boost::apply_visitor(*this, x.rhs);

    /// If both operands are known, we can directly evaluate the function,
    /// else we just update the children with the new expressions.
    if (holds_alternative<double>(lhs) && holds_alternative<double>(rhs)) {
        return x.op(boost::get<double>(lhs), boost::get<double>(rhs));
    }
    return binary_op(x.op, lhs, rhs);
}

ConstantFolder::result_type ConstantFolder::
operator()(ternary_op const &x) const {
    operand p1 = boost::apply_visitor(*this, x.p1);
    operand p2 = boost::apply_visitor(*this, x.p2);
    operand p3 = boost::apply_visitor(*this, x.p3);

    /// If both operands are known, we can directly evaluate the function,
    /// else we just update the children with the new expressions.
    if (holds_alternative<double>(p1) &&
	holds_alternative<double>(p2) &&
	holds_alternative<double>(p3)) {
        return x.op(boost::get<double>(p1), boost::get<double>(p2), boost::get<double>(p3));
    }
    return ternary_op(x.op, p1, p2, p3);
}

} // namespace ast

} // namespace matheval
