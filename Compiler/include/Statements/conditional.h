#if !defined(CONDITIONAL_H)
#define CONDITIONAL_H

#include "../helpers.h"

//TODO: Switch

//input: condition, if-statement, (else-statement)
class IfElseStatement : public Node
{
    nodePtr condition;
    nodePtr statement1;
    nodePtr statement2;
    bool has_else;

public:
    //if statement
    IfElseStatement(nodePtr c, nodePtr s) : condition(c), statement1(s), statement2(nullptr), has_else(false){};
    // if else statement
    IfElseStatement(nodePtr c, nodePtr s1, nodePtr s2) : condition(c), statement1(s1), statement2(s2), has_else(true){};

    void print(std::ostream &out, VariableBindings &bindings) const override;

    ~IfElseStatement()
    {
        delete condition;
        delete statement1;
        delete statement2;
    }
};

// class SwitchStatement : public Node
// {

// };

class WhileStatement : public Node
{
    nodePtr condition;
    nodePtr statement;

public:
    WhileStatement(nodePtr c, nodePtr s)
        : condition(c), statement(s){};

    void print(std::ostream &out, VariableBindings &bindings) const override;

    ~WhileStatement()
    {
        delete condition;
        delete statement;
    }
};

class ForStatement : public Node
{
    nodePtr init;
    nodePtr condition;
    nodePtr alteration;
    nodePtr statement;

public:
    //for(int i = 0; i < x; i++)
    ForStatement(nodePtr e1, nodePtr e2, nodePtr e3, nodePtr s)
        : init(e1), condition(e2), alteration(e3), statement(s){};
    // for(int i = 0; i < x)
    ForStatement(nodePtr e1, nodePtr e2, nodePtr s)
        : init(e1), condition(e2), alteration(nullptr), statement(s){};

    void print(std::ostream &out, VariableBindings &bindings) const override;

    ~ForStatement()
    {
        delete init;
        delete condition;
        delete alteration;
        delete statement;
    }
};

class SwitchStatement : public Node
{
    nodePtr condition;
    nodePtr statement;

public:
    SwitchStatement(nodePtr c, nodePtr s) : condition(c), statement(s){};

    void print(std::ostream &out, VariableBindings &bindings) const override;

    ~SwitchStatement()
    {
        delete condition;
        delete statement;
    };
};

#endif // CONDITIONAL_H
