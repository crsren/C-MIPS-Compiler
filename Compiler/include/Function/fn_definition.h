#if !defined(FN_DEFINITION_H)
#define FN_DEFINITION_H

#include "helpers.h"

class fnDefinition : public Node
{
    fnDefinition();

    void print(std::ostream &out, !!!) const override;

    ~fnDefinition()
    {
    }
};

#endif // FN_DEFINITION_H
