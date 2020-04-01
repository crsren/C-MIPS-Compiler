#include "Statements/compound.h"

void Compound::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    int previousStackFrameSize = bindings->getStackFrameSize();
    
    if (dList)
    for (const auto &declaration : dList->items)
        declaration->print(out, bindings);

    if (sList)
    for (const auto &statement : sList->items)
        statement->print(out, bindings);

    bindings->decrementStackFrameSizeBy(bindings->getStackFrameSize() - previousStackFrameSize);
};