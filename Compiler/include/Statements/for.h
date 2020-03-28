#if !defined(FOR_H)
#define FOR_H

#include "helpers.h"

//input: initial, condition, (alteration), statement
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

#endif // FOR_H
