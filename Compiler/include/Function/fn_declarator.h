#ifndef FN_DECLARATOR_H
#define FN_DECLARATOR_H

#include "helpers.h"
#include "../node.h"

class FnDeclarator : public Node
{
private:
    nodePtr declarator; // identifier
    nodePtr parameterList;      //parameter

public:
    FnDeclarator(nodePtr d, nodePtr l = nullptr) : declarator(d), parameterList(l){};

    virtual void print(std::ostream &out, !!!) const override; //implement

    ~FnDeclarator()
    {
        delete declarator;
        delete parameterList;
    };
};

#endif // FN_DECLARATOR_H
