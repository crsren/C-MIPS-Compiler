#ifndef FN_DEFINITION_H
#define FN_DEFINITION_H

#include "../helpers.h"

class FnDefinition : public Node
{
private:
    nodePtr returnType; //TODO: this should be a Type*
    nodePtr declarator; //TODO: this should be FnDeclarator*
    nodePtr compound;

public:
    FnDefinition(nodePtr declaration_list, nodePtr declarator, nodePtr compound_stmt) : specifier(declaration_list), declarator(declarator), compound(compound_stmt){};

    void print(std::ostream &out, VariableBindings &bindings) const override; //implement
    // cast declarator to a fnDeclarator; access fnDeclarator->paramList and
    // for each item in the list get paramDeclarator->identifier and push into local bindings

    ~FnDefinition()
    {
        delete returnType;
        delete declarator;
        delete compound;
    }
};

#endif // FN_DEFINITION_H
