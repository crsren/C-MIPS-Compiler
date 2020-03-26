#if !defined(BINARYOPERATIONS_H)
#define BINARYOPERATIONS_H

#include "node.h"

#include <string>

class BinaryOperation : public Node
{
private:
    nodePtr l;
    const std::string operator;
    nodePtr r;

public:
    BinaryOperation(nodePtr l, )
}

#endif // BINARYOPERATIONS_H
