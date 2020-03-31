#if !defined(WHILE_H)
#define WHILE_H

#include "../helpers.h"

//input: condition, statement
class WhileStatement : public Node
{
    nodePtr condition;
    nodePtr statement;

public:
    WhileStatement(nodePtr c, nodePtr s)
        : condition(c), statement(s){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;

    ~WhileStatement()
    {
        delete condition;
        delete statement;
    }
};

#endif // WHILE_H
