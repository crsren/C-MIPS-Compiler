#if !defined(BINARY_OPERATION_H)
#define BIANRY_OPERATION_H

#include "helpers.h"

#include <string>

class ArithmeticOperation : public Node
{
private:
    nodePtr left;
    const std::string symbol;
    nodePtr right;

public:
    ArithmeticOperation(nodePtr l, const std::string &s, nodePtr r) : left(l), symbol(s), right(r){};

    void print(std::ostream &out, !!!) const override;
};

#endif // BINARY_OPERATION_H
