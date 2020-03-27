#if !defined(FN_CALL_H)
#define FN_CALL_H

#include "helpers.h"

class FnCall : public Node
{
private:
    nodePtr postfix;
    nodePtr arguments;

public:
    FnCall(nodePtr p, nodePtr a) : postfix(p), arguments(a){};

    void print(std::ostream &out, !!!) const override; //implement

    ~FnCall()
    {
        delete postfix;
        delete arguments;
    }
};

#endif // FN_CALL_H