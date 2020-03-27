#if !defined(COMPOUND_H)
#define COMPOUND_H

#include "helpers.h"

// Input: (node* declarationlist, node* statementlist)
class Compound : public Node()
{
private:
    nodePtr dList; //declaration list
    nodePtr sList; //statement list

public:
    Compound(nodePtr d, nodePtr s) : dList(d), sList(s){};

    ~Compound()
    {
        delete dList;
        delete sList;
    }
};

#endif // COMPOUND_H
