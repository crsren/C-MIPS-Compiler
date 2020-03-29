#ifndef DECLARATION_H
#define DECLARATION_H

#include "node.h"

// for for var, function, (later array?)
class Declaration : public Node
{
    //nodePtr dataType; for now this is a single string
    const std::string declarationSpecifier;
    nodePtr initDeclaratorList; // TO DO: this should be VarDeclarator*

public:
    Declaration(const std::string dS, nodePtr iDL) : declarationSpecifier(dS), initDeclaratorList(iDL){};

    void print(std::ostream &out, VariableBindings &bindings) const override;

    ~Declaration()
    {
        delete initDeclaratorList;
    }
};

#endif // DECLARATION_H