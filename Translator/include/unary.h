#ifndef UNARY_H
#define UNARY_H

#include <iostream>
#include <string>
#include "node.h"

typedef const Node *nodePtr;

using namespace std;

class Unary : public Node
{
private:
    const unsigned char prefix;
    nodePtr expression;

public:
    Unary(const unsigned char &sign, nodePtr exp) : prefix(sign), expression(exp){};

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
