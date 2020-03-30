#if !defined(IF_ELSE_H)
#define IF_ELSE_H

#include "../helpers";

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

    void print(std::ostream &out, LocalVariableBindings &bindings) const override;

    ~IfElseStatement()
    {
        delete condition;
        delete statement1;
        delete statement2;
    }
};

#endif // IF_ELSE_H
