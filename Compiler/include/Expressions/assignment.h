#if !defined(ASSIGNMENT_H)
#define ASSIGNMENT_H

#include "node.h"

#include <string>

class AssignmentExpression : public Node
{
private:
    Node *l;
    Node *r;

public:
    //simple "=", possible associated binary operation has been daelt with in parser
    AssignmentExpression(Node *l, Node *r) : l(l), r(r){};

    void print(std::ostream &out, VariableBindings bindings) const override;
};

#endif // ASSIGNMENT_H
