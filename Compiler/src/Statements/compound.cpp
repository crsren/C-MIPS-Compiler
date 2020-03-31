#include "Statements/compound.h"

void Compound::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    int previousStackFrameSize = bindings->getStackFrameSize();

    for (const auto &declaration : dList->items)
        declaration->print(out, bindings);

    for (const auto &statement : sList->items)
        statement->print(out, bindings);

    bindings->decrementStackFrameSizeBy(bindings->getStackFrameSize() - previousStackFrameSize);
};