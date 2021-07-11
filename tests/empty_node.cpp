#define BOOST_TEST_MODULE empty_node
#define MATHEVAL_IMPLEMENTATION
#include "exprtest.hpp"
#include "ast.hpp"
#include "evaluator.hpp"

BOOST_AUTO_TEST_CASE(empty_node)
{
    matheval::ast::expression ast;
    matheval::ast::eval solver({});
    BOOST_CHECK_EQUAL(solver(ast),0);
}
