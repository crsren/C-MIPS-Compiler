#if !defined(UNARY_H)
#define UNARY_H

#include <iostream>
#include <string>
#include "ASTnode.h"

using namespace std;

class Unary : public Node
{
private:
    nodePtr expression;
    char prefix;

public:
    Unary(const char &sign, nodePtr exp) : prefix(sign), expression(exp){};

    virtual void print(std::ostream &out) const override
    {
        out << prefix;
        expression->print(out);
    }

    ~Unary()
    {
        delete expression;
    }
};

#endif // UNARY_H
