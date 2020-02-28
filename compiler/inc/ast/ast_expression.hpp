#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

#include "ast_node.hpp"

class Expression;

typedef const Expression* ExpressionPtr;

class Expression: public Node
{
public:
    virtual ~Expression()
    {}

    virtual void print(std::ostream &dst) const = 0;

    virtual double evaluate(const std::map<std::string, double> &bindings) const = 0;
};

class ArithmeticExpression: public Expression
{
public:
    
}

#endif
