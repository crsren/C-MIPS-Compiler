#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>

class Expression
{
public:
    virtual ~Expression(){};
    virtual void print(){};
};

typedef const Expression *ExpressionPtr;

#endif // EXPRESSION_H
