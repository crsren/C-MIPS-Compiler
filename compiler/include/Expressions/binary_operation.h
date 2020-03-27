#ifndef BINARY_OPERATION_H
#define BINARY_OPERATION_H

#include "../helpers.h"

class BinaryOperation : public Node
{
protected:
    nodePtr left;
    std::string operationSymbol;
    nodePtr right;

public:
    BinaryOperation(nodePtr l, std::string symbol, nodePtr r) : left(l), operationSymbol(symbol), right(r){};

    virtual void print(std::ostream &out, VariableBindings bindings) const = 0; //implement

    ~BinaryOperation()
    {
        delete left;
        delete right;
    }
};

#endif // OPERATION_H
