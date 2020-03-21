#if !defined(UNARY_H)
#define UNARY_H

#include <iostream>
#include <string>
#include "AST.h"

typedef const Node *nodePtr;

using namespace std;

class Unary : public Node
{
private:
    const string prefix;
    nodePtr expression;

public:
    Unary(const string &sign, nodePtr exp) : prefix(sign), expression(exp){};

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
