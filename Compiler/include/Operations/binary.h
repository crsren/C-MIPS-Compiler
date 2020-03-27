#if !defined(BINARY_H)
#define BIANRY_H

#include "node.h"

#include <string>

class BinaryOperation : public Node
{
private:
    nodePtr left;
    const std::string symbol;
    nodePtr right;

public:
    BinaryOperation(nodePtr l, const std::string &s, nodePtr r) : left(l), symbol(s), right(r){};

    void print(std::ostream &out, !!!) const override;
};

#endif // BINARY_H
