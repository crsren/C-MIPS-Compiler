#if !defined(JUMP_H)
#define JUMP_H

#include "../helpers.h"

class ReturnStatement : public Node
{
private:
    nodePtr expression;

public:
    ReturnStatement(nodePtr e = nullptr) : expression(e){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;

    ~ReturnStatement() { delete expression; };
};

class BreakStatement : public Node
{
public:
    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

class ContinueStatement : public Node
{
    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

#endif // JUMP_H
