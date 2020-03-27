#if !defined(ITERATION_H)
#define ITERATION_H

#include "helpers.h"

class WhileStatement : public Node
{
private:
    nodePtr condition;
    nodePtr statement;

public:
    WhileStatement(nodePtr c, nodePtr s) : condition(c), statement(s){};

    void print(std::ostream &out, VariableBindings bindings) const override; // Implement

    ~WhileStatement()
    {
        delete condition;
        delete statement;
    }
};

#endif // ITERATION_H
