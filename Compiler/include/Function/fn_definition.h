#ifndef FN_DEFINITION_H
#define FN_DEFINITION_H

#include "../helpers.h"

class FnDefinition : public Node
{
private:
    nodePtr specifier; // return type
    nodePtr declarator;
    nodePtr statement;

public:
    FnDefinition(nodePtr declaration_list, nodePtr declarator, nodePtr compound_stmt) : specifier(declaration_list), declarator(declarator), statement(compound_stmt){};

    void print(std::ostream &out, !!!) const override; //implement

    ~FnDefinition()
    {
        delete specifier;
        delete declarator;
        delete statement;
    }
};

#endif // FN_DEFINITION_H
