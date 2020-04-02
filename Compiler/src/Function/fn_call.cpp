#include "Function/fn_call.h"

void FnCall::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << "FnCall::print\tSTART\n";

    std::cerr << "Printing MIPS code\n";
    out << Mips::sub_(29, 29, bindings->getStackFrameSize()); // note $sp = $29

    int stackFrameOffset = 8;

    if (argumentList)
    {
        std::cerr << "For (evey argument int the argument list)\n";
        for (const auto argument : argumentList->items)
        {
            std::cerr << "\t**************************\n";
            std::cerr << "\tLoop Iteration:" << std::to_string(stackFrameOffset / 4 - 2) << "\n";
            std::cerr << "\tPrint the current argument\n";
            argument->print(out, bindings);
            std::cerr << "\tPrinting MIPS code\n";
            out << Mips::store_word(2, stackFrameOffset, true);
            std::cerr << "\tIncrement stackFrameOffset\n";
            stackFrameOffset += 4;
            std::cerr << "\t**************************\n\n";
            // store answer that is in register $2
        }
    }

    std::cerr << "Cast the identifier to a pointer to an Identifier\n";
    const Identifier *casted_id = dynamic_cast<const Identifier *>(identifier);

    if (casted_id == nullptr)
    {
        std::cerr << "if (the identifier cannot be casted to an Identifier)\n";
        std::cerr << "\tThat is not supported yet\n";
    }

    std::cerr << "\tGet the function identifier\n";
    std::string functionIdentifier = casted_id->getName();

    std::cerr << "Printing MIPS code\n";
    Mips::jal(functionIdentifier);

    std::cerr << "FnCall::print\tEND\n";
};