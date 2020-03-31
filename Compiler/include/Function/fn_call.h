#ifndef FN_CALL_H
#define FN_CALL_H

#include "helpers.h"
#include "Expressions/primitives.h"

class FnCall : public Node
{
private:
    Identifier *identifier;
    List *argumentList;

public:
    FnCall(Identifier *p, List *a) : identifier(p), argumentList(a){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;

    ~FnCall()
    {
        delete identifier;
        delete argumentList;
    }
};

#endif // FN_CALL_H