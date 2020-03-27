#if !defined(UNARY_OPERATION_H)
#define UNARY_OPERATION_H

#include "helpers.h"

// '&' '*' '+' '-' '~' '!'
class UnaryOperation : public Node
{
private:
    const unsigned char symbol;
    nodePtr expression;

public:
    UnaryOperation(const unsigned char symbol, nodePtr expression) : symbol(symbol), expression(expression){};

    void print(std::ostream &out, !!!) const override; //implement

    ~UnaryOperation()
    {
        delete expression;
    }
};

/// Later:
// class preOperation: ++n, --n
//c lass postOperation: n++, n--

#endif // UNARY_OPERATION_H
