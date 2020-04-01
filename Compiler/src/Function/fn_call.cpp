#include "Function/fn_call.h"

void FnCall::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    out << Mips::sub_(29, 29, bindings->getStackFrameSize()); // note $sp = $29

    int stackFrameOffset = 8;

    for (const auto argument : argumentList->items)
    {
        argument->print(out, bindings);
        out << Mips::store_word(2, stackFrameOffset, true);
        stackFrameOffset += 4;
        // store answer that is in register $2
    }
    const Identifier *casted_id = dynamic_cast<const Identifier *>(identifier);
    if (casted_id == nullptr)
        std::cerr << "FnCall: Could not cast Node to Identifier.\n";

    std::string functionIdentifier = casted_id->getName();

    Mips::jal(functionIdentifier);
};