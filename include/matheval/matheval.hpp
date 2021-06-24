#pragma once

#include <map>
#include <memory>
#include <string>

namespace matheval {

/// @brief Parse a mathematical expression
///
/// This can parse and evaluate a mathematical expression for a given
/// symbol table using Boost.Spirit X3.  The templates of Boost.Spirit
/// are very expensive to parse and instantiate, which is why we hide
/// it behind an opaque pointer.
///
/// The drawback of this approach is that calls can no longer be
/// inlined and because the pointer crosses translation unit
/// boundaries, dereferencing it can also not be optimized out at
/// compile time.  We have to rely entirely on link-time optimization
/// which might be not as good.
///
/// The pointer to the implementation is a std::unique_ptr which makes
/// the class not copyable but only moveable.  Copying shouldn't be
/// required but is easy to implement.
class Parser {
    class impl;
    std::unique_ptr<impl> pimpl;

public:
    /// @brief Constructor
    Parser();

    /// @brief Destructor
    ~Parser();

    /// @brief Parse the mathematical expression into an abstract syntax tree
    ///
    /// @param[in] expr The expression given as a std::string
    void parse(std::string const &expr);

    /// @brief Perform constant folding onto the abstract syntax tree
    void optimize();

    /// @brief Evaluate the abstract syntax tree for a given symbol table
    ///
    /// @param[in] st The symbol table
    double evaluate(std::map<std::string, double> const &st = {});
};

/// @brief Convenience function
///
/// This function builds the grammar, parses the iterator to an AST,
/// evaluates it, and returns the result.
///
/// @param[in] expr  mathematical expression
/// @param[in] st    the symbol table for variables
inline double parse(std::string const &expr,
                    std::map<std::string, double> const &st = {}) {
    Parser parser;
    parser.parse(expr);
    return parser.evaluate(st);
}

class exception : public std::runtime_error
{
public:
  explicit exception(const std::string& what_arg) : std::runtime_error(what_arg) {}
  explicit exception(const char* what_arg) : std::runtime_error(what_arg) {}
};

class divideByZero : public exception
{
public:
  divideByZero() : exception("divide by zero") {}
  explicit divideByZero(const char *what) : exception(what) {}
};

class moduloByZero : public divideByZero
{
public:
  moduloByZero() : divideByZero("modulo by zero") {}
};

class moduloWithInfinity : public exception
{
public:
  moduloWithInfinity() : exception("modulo with infinity") {}
};

class powInvalid : public exception
{
public:
  powInvalid() : exception("pow invalid parameter") {}
};

class powDivideByZero : public divideByZero
{
public:
  powDivideByZero() : divideByZero("pow divide by zero") {}
};

class powOverflow : public exception
{
public:
  powOverflow() : exception("pow overflow") {}
};

class powUnderflow : public exception
{
public:
  powUnderflow() : exception("pow underflow") {}
};

class acosInvalid : public exception
{
public:
  explicit acosInvalid(double d) : exception("invalid acos "+std::to_string(d)) {}
};

class acoshInvalid : public exception
{
public:
  explicit acoshInvalid(double d) : exception("invalid acosh "+std::to_string(d)) {}
};

class asinInvalid : public exception
{
public:
  explicit asinInvalid(double d) : exception("invalid asin "+std::to_string(d)) {}
};

class atanhInvalid : public exception
{
public:
  explicit atanhInvalid(double d) : exception("invalid atanh "+std::to_string(d)) {}
};

class atanhDivideByZero : public divideByZero
{
public:
  atanhDivideByZero() : divideByZero("atanh divide by zero") {}
};

class cosInvalid : public exception
{
public:
  explicit cosInvalid() : exception("invalid cos") {}
};

class logInvalid : public exception
{
public:
  explicit logInvalid(double d) : exception("invalid logarithm "+std::to_string(d)) {}
};

class logDivideByZero : public divideByZero
{
public:
  logDivideByZero() : divideByZero("logarithm divide by zero") {}
};

class sinInvalid : public exception
{
public:
  sinInvalid() : exception("invalid sin") {}
};

class sqrtInvalid : public exception
{
public:
  explicit sqrtInvalid(double d) : exception("invalid sqrt "+std::to_string(d)) {}
};

class tanInvalid : public exception
{
public:
  tanInvalid() : exception("invalid tan") {}
};

class tgammaDivideByZero : public divideByZero
{
public:
  tgammaDivideByZero() : divideByZero("tgamma divide by zero") {}
};

class tgammaInvalid : public exception
{
public:
  explicit tgammaInvalid(double d) : exception("invalid tgamma "+std::to_string(d)) {}
};

} // namespace matheval
