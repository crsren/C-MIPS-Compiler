#include "Statements/compound.h"

void Compound::print(std::ostream &out, VariableBindings bindings) const
{
    //enter scope

    for (const auto &declaration : dList)
        declaration->print(out, bindings);

    for (const auto &statement : sList)
        statement->print(out, bindings);

    // levae scope
};