#ifndef UNARY_OPERATION_H
#define UNARY_OPERATION_H

#include "../helpers.h"

// '&' '*' '+' '-' '~' '!'
class UnaryOperation : public Node
{
private:
    const unsigned char operationSymbol;
    nodePtr unaryExpression;

public:
    UnaryOperation(const unsigned char s, nodePtr uExp) : operationSymbol(s), unaryExpression(uExp){};

    ~UnaryOperation()
    {
        delete unaryExpression;
    }

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        
    }
};

/// Later:
// class preOperation: ++n, --n
//c lass postOperation: n++, n--

#endif // UNARY_OPERATION_H
