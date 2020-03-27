#ifndef BINARYOPERATIONS_H
#define BINARYOPERATIONS_H

#include "node.h"

#include <string>

class BinaryOperation : public Node
{
private:
    Node* left;
    const std::string operator;
    Node* right;

public:
    BinaryOperation(nodePtr l, );

}

#endif // BINARYOPERATIONS_H
