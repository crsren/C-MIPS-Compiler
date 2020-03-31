#ifndef FN_PARAMETER_H
#define FN_PARAMETER_H

#include "../helpers.h"

class FnParameterDeclaration : public Node
{
    nodePtr specifiers;
    nodePtr declarator;

public:
    FnParameterDeclaration(nodePtr s, nodePtr d) : specifiers(s), declarator(d){};

    void print(std::ostream &out, LocalVariableBindings bindings) const override; // implement

    ~FnParameterDeclaration()
    {
        delete specifiers;
        delete declarator;
    }
};

#endif // FN_PARAMETER_H
