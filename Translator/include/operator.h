#ifndef OPERATORS_H
#define OPERATORS_H

#include "ASTnode.h"
#include <string>

class Operator : public Node
{
private:
    nodePtr l;
    nodePtr r;
    std::string opCode; // "+" etc.

protected:
    Operator(nodePtr left, const char &symbol, nodePtr right) : l(left), r(right)
    {
        opCode = "";
        opCode += symbol;
    };
    Operator(nodePtr left, const std::string &symbol, nodePtr right) : opCode(symbol), l(left), r(right){};

public:
    virtual void print(std::ostream &out) const override
    {
        l->print(out);
        out << " " << opCode << " ";
        r->print(out);
    }

    virtual ~Operator()
    {
        delete l;
        delete r;
    }
};

#endif //OPERATORS_H