#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>

class Expression
{
public:
    virtual ~Expression(){};
    virtual void print(){}; //printing python equivalent
};

typedef const Expression *ExpressionPtr;

#endif // EXPRESSION_H
