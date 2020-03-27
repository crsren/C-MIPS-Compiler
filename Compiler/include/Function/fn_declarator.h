#if !defined(FN_DECLARATOR_H)
#define FN_DECLARATOR_H

#include "helpers.h"

class FnDeclarator : public Node
{
private:
    nodePtr declarator; // identifier
    nodePtr pList;      //parameter

public:
    FnDeclarator(nodePtr d, nodePtr l = nullptr) : declarator(d), pList(l){};

    virtual void print(std::ostream &out, !!!) const override; //implement

    ~FnDeclarator()
    {
        delete declarator;
        delete list;
    };
};

#endif // FN_DECLARATOR_H
