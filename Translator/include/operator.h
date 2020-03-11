#ifndef OPERATORS_H
#define OPERATORS_H

#include "AST.h"
#include <string>

typedef const Node *nodePtr;

class Operator : public Node
{
private:
    nodePtr l;
    std::string opCode; // "+" etc.
    nodePtr r;

protected:
    Operator(nodePtr left, const char &symbol, nodePtr right) : l(left), r(right)
    {
        opCode = "";
        opCode += symbol;
    };
    Operator(nodePtr left, const std::string &symbol, nodePtr right) : l(left), opCode(symbol), r(right){};

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