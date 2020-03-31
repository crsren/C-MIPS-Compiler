#ifndef FN_DEFINITION_H
#define FN_DEFINITION_H

#include "../helpers.h"
#include "fn_declarator.h"

class FnDefinition : public Node
{
private:
    /*nodePtr*/
    const std::string returnType; //TODO: this should be a Type*
    FnDeclarator *fnDeclarator;
    nodePtr compound;

public:
    FnDefinition(std::string declaration_list, FnDeclarator *declarator, nodePtr compound_stmt) : returnType(declaration_list), fnDeclarator(declarator), compound(compound_stmt){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override; //implement
    // cast declarator to a fnDeclarator; access fnDeclarator->paramList and
    // for each item in the list get paramDeclarator->identifier and push into local bindings

    ~FnDefinition()
    {
        delete fnDeclarator;
        delete compound;
    }
};

#endif // FN_DEFINITION_H
