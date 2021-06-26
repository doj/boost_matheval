#define MATHEVAL_IMPLEMENTATION

#include "matheval.hpp"
#include "ast.hpp"
#include "../evaluator.hpp"
#include "parser.hpp"

#include <memory>
#include <stdexcept>
#include <string>

namespace matheval {

class Parser::impl {
    ast::operand ast;

public:
    void parse(std::string const &expr) {
        ast::expression ast_;

        std::string::const_iterator first = expr.begin();
        std::string::const_iterator last = expr.end();

        boost::spirit::ascii::space_type space;
        bool r = qi::phrase_parse(
            first, last, grammar(), space,
            ast_);

        if (!r || first != last) {
            std::string rest(first, last);
            throw std::runtime_error("Parsing failed at " + rest); // NOLINT
        }

        ast = ast_;
    }

    void optimize() { ast = boost::apply_visitor(ast::ConstantFolder(), ast); }

    double evaluate(Parser::variable_callback_fn fn) {
        return boost::apply_visitor(ast::eval(fn), ast);
    }
};

Parser::Parser() : pimpl(new Parser::impl()) {}

Parser::~Parser() {}

void Parser::parse(std::string const &expr) { pimpl->parse(expr); }

void Parser::optimize() { pimpl->optimize(); }

double Parser::evaluate(Parser::variable_callback_fn fn) {
    return pimpl->evaluate(fn);
}

} // namespace matheval
