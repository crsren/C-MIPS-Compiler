#include "Statements/compound.h"

void Compound::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << "Compound::print\tSTART\n";

    std::cerr << "Get stack frame size\n";
    int previousStackFrameSize = bindings->getStackFrameSize();

    if (dList)
    {
        std::cerr << "if (the declaration list is not a nullptr)\n";
        std::cerr << "\tfor (evey declaration element in the declaration list)\n";
        for (const auto &declaration : dList->items)
        {
            std::cerr << "\t\t**************************\n";
            std::cerr << "\t\tPrint the current declaration element\n";
            declaration->print(out, bindings);
            std::cerr << "\t\t**************************\n\n";
        }
    }

    if (sList)
    {
        std::cerr << "for (evey statement element in the statement list)\n";
        for (const auto &statement : sList->items)
        {
            std::cerr << "\tif (the statement list is not a nullptr)\n";
            std::cerr << "\t\t**************************\n";
            std::cerr << "\t\tPrint the current statement element\n";
            statement->print(out, bindings);
            std::cerr << "\t\t**************************\n\n";
        }
    }

    std::cerr << "Decrement the local stack frame size by" << std::to_string(bindings->getStackFrameSize() - previousStackFrameSize) << "\n";
    bindings->decrementStackFrameSizeBy(bindings->getStackFrameSize() - previousStackFrameSize);

    std::cerr << "Compound::print\tEND\n";
};