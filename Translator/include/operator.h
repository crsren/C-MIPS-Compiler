#ifndef OPERATORS_H
#define OPERATORS_H

#include <string>
#include "node.h"

class Operator : public Node
{
private:
    nodePtr l;
    std::string opCode; // "+" etc.
    nodePtr r;

public:
    Operator(nodePtr left, const unsigned char &symbol, nodePtr right) : l(left), r(right)
    {
        opCode = "";
        opCode += symbol;
    };
    Operator(nodePtr left, const std::string &symbol, nodePtr right) : l(left), opCode(symbol), r(right){};

    virtual void print(std::ostream &out) const override
    {
        out << "(";
        l->print(out);
        out << " " << opCode << " ";
        r->print(out);
        out << ")";
    }

    virtual ~Operator()
    {
        delete l;
        delete r;
    }
};

#endif //OPERATORS_H