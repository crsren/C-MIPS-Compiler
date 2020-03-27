#if !defined(OPERATION_H)
#define OPERATION_H

#include "helpers";

class BinaryOperation : public Node
{
    nodePtr left;
    std::string operator;
    nodePtr right;

    BinaryOperation(nodePtr l, std::string symbol, nodePtr r) : left(l), operator(symbol), right(r){};

    void print(std::ostream &out, !!!) const override; //implement

    ~BinaryOperation()
    {
        delete left;
        delete right;
    }
};

#endif // OPERATION_H
