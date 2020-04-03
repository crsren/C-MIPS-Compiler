#ifndef UNARY_OPERATION_H
#define UNARY_OPERATION_H

#include "../helpers.h"

// '&' '*' '+' '-' '~' '!'
class UnaryOperation : public Node
{
private:
    const std::string operationSymbol;
    nodePtr postfixExpression;

public:
    UnaryOperation(std::string s, nodePtr uExp) : operationSymbol(s), postfixExpression(uExp){};

    ~UnaryOperation()
    {
        delete postfixExpression;
    }

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

// ++x, --x
class PreOperation : public Node
{
    const unsigned char symbol;
    nodePtr expression;

public:
    PreOperation(nodePtr e, const unsigned char c) : expression(e), symbol(c){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

// x++, x--
class PostOperation : public Node
{
    const unsigned char symbol;
    nodePtr expression;

public:
    PostOperation(const unsigned char c, nodePtr e) : symbol(c), expression(e){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

#endif // UNARY_OPERATION_H
