#include "Function/fn_call.h"

void FnCall::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "FnCall::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
    out << Mips::sub_(29, 29, bindings->getStackFrameSize()); // note $sp = $29

    int stackFrameOffset = 8;

    // KIMON: To get argumentList size: ( => amount of parameters of the called function ):
    // int argListSize = argumentList->getSize();

    std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument int the argument list)\n";
    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";

    std::list<nodePtr> &arguments = argumentList->getItems();
    for (const auto &argument : arguments)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
        std::cerr << GlobalIndent::instance().globalIndent << "Loop Iteration:" << std::to_string(stackFrameOffset / 4 - 2) << "\n";
        std::cerr << GlobalIndent::instance().globalIndent << "Print the current argument\n";
        argument->print(out, bindings);
        std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
        out << Mips::store_word(2, stackFrameOffset, true);
        std::cerr << GlobalIndent::instance().globalIndent << "Increment stackFrameOffset\n";
        stackFrameOffset += 4;
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
        // store answer that is in register $2
    }
    GlobalIndent::instance().globalIndent = oldGlobalIndent;

    std::cerr << GlobalIndent::instance().globalIndent << "Cast the identifier to a pointer to an Identifier\n";
    const Identifier *casted_id = dynamic_cast<const Identifier *>(identifier);

    if (casted_id == nullptr)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the identifier cannot be casted to an Identifier)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tThat is not supported yet\n";
    }

    std::cerr << GlobalIndent::instance().globalIndent << "\tGet the function identifier\n";
    std::string functionIdentifier = casted_id->getName();

    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
    Mips::jal(functionIdentifier);

    std::cerr << GlobalIndent::instance().globalIndent << "FnCall::print\tEND\n";
};