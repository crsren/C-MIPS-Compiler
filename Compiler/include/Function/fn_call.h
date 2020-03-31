#ifndef FN_CALL_H
#define FN_CALL_H

#include "../helpers.h"

class FnCall : public Node
{
private:
    Identifier* identifier;
    ListPtr argumentList; 

public:
    FnCall(nodePtr p, nodePtr a) : postfix(p), argumentList(a){};

    void print(std::ostream &out, LocalVariableBindings bindings) const override;

    ~FnCall()
    {
        delete postfix;
        delete argumentList;
    }
};



#endif // FN_CALL_H