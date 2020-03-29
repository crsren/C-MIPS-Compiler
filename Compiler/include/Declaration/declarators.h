#ifndef DECLARATOR_H
#define DECLARATOR_H

#include "helpers.h"

class VarDeclarator
{
    const std::string identifier;

public:
    VarDeclarator(const std::string &s) identifier(s){};
};

//TODO: class ArrayDeclarator

class InitDeclarator
{
    nodePtr declarator; // TO DO: is it always a VarDeclarator*??
    nodePtr initializer;

public:
    InitDeclarator(nodePtr d, nodePtr i) : declarator(d), initializer(i){};
    InitDeclarator(nodePtr d) : declarator(d), initializer(nullptr){};

    void print(std::ostream &out, VariableBindings &bindings) const override;

    ~InitDeclarator()
    {
        delete declarator;
        delete initializer;
    }
};

#endif // DECLARATOR_H
