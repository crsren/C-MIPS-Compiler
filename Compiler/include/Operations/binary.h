#if !defined(BINARY_H)
#define BIANRY_H

#include "node.h"

#include <string>

class BinaryOperation : public Node
{
private:
    Node *left;
    const std::string symbol;
    Node *right;

public:
    BinaryOperation(Node *l, const std::string &s, Node *r) : left(l), symbol(s), right(r){};

    void print(std::ostream &out, !!!) const override;
};

#endif // BINARY_H
