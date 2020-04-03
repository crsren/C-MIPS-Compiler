#include "Function/fn_call.h"

void FnCall::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "FnCall::print\tSTART\n";

    if (bindings)
    {
        //std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
        //out << Mips::sub_(29, 29, bindings->getStackFrameSize()); // note $sp = $29

        //int stackFrameOffset = 8;

        // KIMON: To get argumentList size: ( => amount of parameters of the called function ):
        // int argListSize = argumentList->getSize();

        int argumentListSize = 0;
        std::vector<nodePtr> arguments;
        if (argumentList)
        {
            argumentList->getSize();
            arguments = argumentList->getItems();
        }

        std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "argumentListSize: " << argumentListSize << "\n";
        std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t";

        int i;
        for (i = argumentListSize - 1; i >= 4; i--)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Loop Iteration:" << std::to_string(argumentListSize - i) << "\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current argument\n";
            arguments[i]->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
            out << Mips::store_word(2, bindings->getStackFrameSize(), false);
            std::cerr << GlobalIndent::instance().globalIndent << "Increment localStackFrameSize\n";
            bindings->incrementStackFrameSize();
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
            // store answer that is in register $2
        }
        GlobalIndent::instance().globalIndent = oldGlobalIndent;

        std::cerr << GlobalIndent::instance().globalIndent << "For (the first 4 arguments in the argument list)\n";
        oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t";

        for (int j = i; j >= 0; j--)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Loop Iteration:" << std::to_string(i - j) << "\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current argument\n";
            arguments[j]->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
            out << Mips::store_word(2, -(j + 1), false);
            std::cerr << GlobalIndent::instance().globalIndent << "Increment localStackFrameSize\n";
            bindings->incrementStackFrameSize();
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
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
        out << Mips::addi(29, 29, 4-bindings->getStackFrameSize());
        out << Mips::jal(functionIdentifier);
    }
    else
    {
        //std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
        //out << Mips::sub_(29, 29, bindings->getStackFrameSize()); // note $sp = $29

        //int stackFrameOffset = 8;

        // KIMON: To get argumentList size: ( => amount of parameters of the called function ):
        // int argListSize = argumentList->getSize();

        int argumentListSize = argumentList->getSize();

        std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
        std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t";

        std::vector<nodePtr> arguments = argumentList->getItems();

        int i;
        for (i = argumentListSize - 1; i >= 4; i--)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Loop Iteration:" << std::to_string(argumentListSize - i) << "\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current argument\n";
            arguments[i]->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
            out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
            std::cerr << GlobalIndent::instance().globalIndent << "Increment localStackFrameSize\n";
            GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
            // store answer that is in register $2
        }
        GlobalIndent::instance().globalIndent = oldGlobalIndent;

        std::cerr << GlobalIndent::instance().globalIndent << "For (the first 4 arguments in the argument list)\n";
        oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t";

        for (int j = i; j >= 0; j--)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Loop Iteration:" << std::to_string(i - j) << "\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current argument\n";
            arguments[j]->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
            out << Mips::store_word(2, -(j + 1), false);
            std::cerr << GlobalIndent::instance().globalIndent << "Increment globalStackFrameSize\n";
            GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
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
        out << Mips::addi(29, 29, 4-GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset());
        out << Mips::jal(functionIdentifier);
    }
    

    std::cerr << GlobalIndent::instance().globalIndent << "FnCall::print\tEND\n";
};