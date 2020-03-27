#if !defined(ASSIGNMENT_H)
#define ASSIGNMENT_H

#include "helpers.h"

#include <string>

class AssignmentExpression : public Node
{
private:
    nodePtr l;
    nodePtr r;

public:
    //simple "=", possible associated binary operation has been daelt with in parser
    AssignmentExpression(nodePtr l, nodePtr r) : l(l), r(r){};

    void print(std::ostream &out, !!!) const override;
};

#endif // ASSIGNMENT_H
