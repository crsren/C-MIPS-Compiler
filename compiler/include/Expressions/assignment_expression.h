#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include "../helpers.h"

#include <string>

class AssignmentExpression : public Node
{
private:
    nodePtr left;
    nodePtr right;

public:
    //simple "=", possible associated binary operation has been daelt with in parser
    AssignmentExpression(Node *l, Node *r) : left(l), right(r){};

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        
    }
};

#endif // ASSIGNMENT_H
