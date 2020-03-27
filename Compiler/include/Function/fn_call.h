#ifndef FN_CALL_H
#define FN_CALL_H

#include "helpers.h"

class FnCall : public Node
{
private:
    nodePtr postfix;
    nodePtr argumentList;

public:
    FnCall(nodePtr p, nodePtr a) : postfix(p), argumentList(a){};

    void print(std::ostream &out, !!!) const override;

    ~FnCall()
    {
        delete postfix;
        delete argumentList;
    }
};

#endif // FN_CALL_H