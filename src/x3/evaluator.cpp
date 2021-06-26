#define MATHEVAL_IMPLEMENTATION

#include "../evaluator.hpp"
#include "ast.hpp"

namespace matheval {

namespace ast {

// Optimizer

template <typename T>
struct holds_alternative_impl {
    using result_type = bool;

    template <typename U>
    bool operator()(U const &) const {
        return std::is_same<U, T>::value;
    }
};

template <typename T, typename... Ts>
bool holds_alternative(x3::variant<Ts...> const &v) {
    return boost::apply_visitor(holds_alternative_impl<T>(), v);
}

ConstantFolder::result_type ConstantFolder::
operator()(std::string const &c) const {
    return result_type{c};
}

ConstantFolder::result_type ConstantFolder::
operator()(operation const &x, operand const &lhs) const {
    auto rhs = boost::apply_visitor(*this, x.rhs);

    if (holds_alternative<double>(lhs) && holds_alternative<double>(rhs)) {
        return result_type{
            x.op(boost::get<double>(lhs), boost::get<double>(rhs))};
    }
    return result_type{binary_op{x.op, lhs, rhs}};
}

ConstantFolder::result_type ConstantFolder::
operator()(unary_op const &x) const {
    auto rhs = boost::apply_visitor(*this, x.rhs);

    /// If the operand is known, we can directly evaluate the function.
    if (holds_alternative<double>(rhs)) {
        return result_type{x.op(boost::get<double>(rhs))};
    }
    return result_type{unary_op{x.op, rhs}};
}

ConstantFolder::result_type ConstantFolder::
operator()(binary_op const &x) const {
    auto lhs = boost::apply_visitor(*this, x.lhs);
    auto rhs = boost::apply_visitor(*this, x.rhs);

    /// If both operands are known, we can directly evaluate the function,
    /// else we just update the children with the new expressions.
    if (holds_alternative<double>(lhs) && holds_alternative<double>(rhs)) {
        return result_type{
            x.op(boost::get<double>(lhs), boost::get<double>(rhs))};
    }
    return result_type{binary_op{x.op, lhs, rhs}};
}

ConstantFolder::result_type ConstantFolder::
operator()(ternary_op const &x) const {
    auto p1 = boost::apply_visitor(*this, x.p1);
    auto p2 = boost::apply_visitor(*this, x.p2);
    auto p3 = boost::apply_visitor(*this, x.p3);

    /// If all operands are known, we can directly evaluate the function,
    /// else we just update the children with the new expressions.
    if (holds_alternative<double>(p1) &&
	holds_alternative<double>(p2) &&
	holds_alternative<double>(p3)) {
        return result_type{
            x.op(boost::get<double>(p1), boost::get<double>(p2), boost::get<double>(p3))};
    }
    return result_type{ternary_op{x.op, p1, p2, p3}};
}

} // namespace ast

} // namespace matheval
