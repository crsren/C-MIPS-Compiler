#include "Statements/compound.h"

void Compound::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "Compound::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Get stack frame size\n";
    int previousStackFrameSize = bindings->getStackFrameSize();

    if (dList)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the declaration list is not a nullptr)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tfor (evey declaration element in the declaration list)\n";
        std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t\t";
        for (const auto &declaration : dList->items)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current declaration element\n";
            declaration->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
        }
        GlobalIndent::instance().globalIndent = oldGlobalIndent;
    }

    if (sList)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the statement list is not a nullptr)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tfor (evey statement element in the statement list)\n";
        std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t\t";
        for (const auto &statement : sList->items)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current statement element\n";
            statement->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
        }
        GlobalIndent::instance().globalIndent = oldGlobalIndent;
    }

    std::cerr << GlobalIndent::instance().globalIndent << "Decrement the local stack frame size by" << std::to_string(bindings->getStackFrameSize() - previousStackFrameSize) << "\n";
    bindings->decrementStackFrameSizeBy(bindings->getStackFrameSize() - previousStackFrameSize);

    std::cerr << GlobalIndent::instance().globalIndent << "Compound::print\tEND\n";
};