#if !defined(FN_CALL_H)
#define FN_CALL_H

#include "helpers.h"

class fnCall : public Node
{
private:
    nodePtr postfix;
    nodePtr arguments;

public:
    fnCall(nodePtr p, nodePtr a) : postfix(p), arguments(a){};

    void print(std::ostream &out, !!!) const override;

    ~fnCall()
    {
        delete postfix;
        delete arguments;
    }
};

#endif // FN_CALL_H