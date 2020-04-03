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
        std::cerr << GlobalIndent::instance().globalIndent << "getting the argumentList\n";
        int argumentListSize = 0;
        std::vector<nodePtr> arguments;
        if (argumentList)
        {
            argumentListSize = argumentList->getSize();
            arguments = argumentList->getItems();
        }

        std::cerr << GlobalIndent::instance().globalIndent << "argumentListSize: " << argumentListSize << "\n";

        if (argumentListSize <= 4)
        {
            std::cerr << "if (the argument list size is <= 4)";
            std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
            std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
            for (int j = argumentListSize - 1; j >= 0; j--)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Printing Mips code\n";
                out << Mips::store_word(j + 4, bindings->getCurrentExpressionAddressOffset(), false);
                std::cerr << GlobalIndent::instance().globalIndent << "Incrementing the currentExpressionAddressOffset\n";
                bindings->incrementCurrentExpressionAddressOffset();
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }
        else
        {
            std::cerr << "if (the argument list size is > 4)";
            std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
            std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
            for (int j = 3; j >= 0; j--)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Printing Mips code\n";
                out << Mips::store_word(j + 4, bindings->getCurrentExpressionAddressOffset(), false);
                std::cerr << GlobalIndent::instance().globalIndent << "Incrementing the currentExpressionAddressOffset\n";
                bindings->incrementCurrentExpressionAddressOffset();
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }

        std::cerr << GlobalIndent::instance().globalIndent << "Getting the before_function_call stack info\n";
        int arg_0_AddressOffset = bindings->getCurrentExpressionAddressOffset();
        int arg_0_StackFrameSize = bindings->getStackFrameSize();

        std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
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
        out << Mips::addi(29, 29, 4 - bindings->getStackFrameSize());
        out << Mips::jal(functionIdentifier);

        std::cerr << GlobalIndent::instance().globalIndent << "Decrement the stack frame size by" << std::to_string(bindings->getStackFrameSize() - arg_0_StackFrameSize) << "\n";
        std::cerr << GlobalIndent::instance().globalIndent << "*****1*****arg_0_AddressOffset:" << arg_0_AddressOffset << " | currentExpressionAddressOffset: " << bindings->getCurrentExpressionAddressOffset() << " | stckFrameSize: " << bindings->getStackFrameSize() << "\n";
        bindings->decrementStackFrameSizeBy(bindings->getStackFrameSize() - arg_0_StackFrameSize);
        std::cerr << GlobalIndent::instance().globalIndent << "*****2*****arg_0_AddressOffset:" << arg_0_AddressOffset << " | currentExpressionAddressOffset: " << bindings->getCurrentExpressionAddressOffset() << " | stckFrameSize: " << bindings->getStackFrameSize() << "\n";

        if (argumentListSize <= 4)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (argumentListSize <= 4)\n";
            oldGlobalIndent = GlobalIndent::instance().globalIndent;
            GlobalIndent::instance().globalIndent += "\t";
            for (int j = 0; j < argumentListSize; j++)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Decrement currentExpressionAddressOffset\n";
                bindings->decrementCurrentExpressionAddressOffset();
                std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
                out << Mips::load_word(j + 4, bindings->getCurrentExpressionAddressOffset(), false);
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }
        else
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (argumentListSize <= 4)\n";
            oldGlobalIndent = GlobalIndent::instance().globalIndent;
            GlobalIndent::instance().globalIndent += "\t";
            for (int j = 0; j < 4; j++)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Decrement currentExpressionAddressOffset\n";
                bindings->decrementCurrentExpressionAddressOffset();
                std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
                out << Mips::load_word(j + 4, bindings->getCurrentExpressionAddressOffset(), false);
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }

        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
    }
    else
    {
        //std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
        //out << Mips::sub_(29, 29, bindings->getStackFrameSize()); // note $sp = $29

        //int stackFrameOffset = 8;

        // KIMON: To get argumentList size: ( => amount of parameters of the called function ):
        // int argListSize = argumentList->getSize();

        std::cerr << GlobalIndent::instance().globalIndent << "getting the argumentList\n";
        int argumentListSize = 0;
        std::vector<nodePtr> arguments;
        if (argumentList)
        {
            argumentListSize = argumentList->getSize();
            arguments = argumentList->getItems();
        }

        std::cerr << GlobalIndent::instance().globalIndent << "argumentListSize: " << argumentListSize << "\n";

        if (argumentListSize <= 4)
        {
            std::cerr << "if (the argument list size is <= 4)";
            std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
            std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
            for (int j = argumentListSize - 1; j >= 0; j--)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Printing Mips code\n";
                out << Mips::store_word(j + 4, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
                std::cerr << GlobalIndent::instance().globalIndent << "Incrementing the currentExpressionAddressOffset\n";
                GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }
        else
        {
            std::cerr << "if (the argument list size is > 4)";
            std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
            std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
            for (int j = 3; j >= 0; j--)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Printing Mips code\n";
                out << Mips::store_word(j + 4, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
                std::cerr << GlobalIndent::instance().globalIndent << "Incrementing the currentExpressionAddressOffset\n";
                GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }

        std::cerr << GlobalIndent::instance().globalIndent << "Getting the before_function_call stack info\n";
        int arg_0_AddressOffset = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();
        int arg_0_StackFrameSize = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();

        std::cerr << GlobalIndent::instance().globalIndent << "For (evey argument in the argument list)\n";
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
        out << Mips::addi(29, 29, 4 - GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset());
        out << Mips::jal(functionIdentifier);

        std::cerr << GlobalIndent::instance().globalIndent << "Decrement the stack frame size by" << std::to_string(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() - arg_0_StackFrameSize) << "\n";
        std::cerr << GlobalIndent::instance().globalIndent << "*****1*****arg_0_AddressOffset:" << arg_0_AddressOffset << " | currentExpressionAddressOffset: " << GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() << " | stckFrameSize: " << GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() << "\n";
        GlobalVariableBindings::instance().decrementCurrentGlobalExpressionAddressOffsetBy(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() - arg_0_StackFrameSize);
        std::cerr << GlobalIndent::instance().globalIndent << "*****2*****arg_0_AddressOffset:" << arg_0_AddressOffset << " | currentExpressionAddressOffset: " << GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() << " | stckFrameSize: " << GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() << "\n";

        if (argumentListSize <= 4)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (argumentListSize <= 4)\n";
            oldGlobalIndent = GlobalIndent::instance().globalIndent;
            GlobalIndent::instance().globalIndent += "\t";
            for (int j = 0; j < argumentListSize; j++)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Decrement currentExpressionAddressOffset\n";
                GlobalVariableBindings::instance().decrementCurrentGlobalExpressionAddressOffset();
                std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
                out << Mips::load_word(j + 4, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }
        else
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (argumentListSize <= 4)\n";
            oldGlobalIndent = GlobalIndent::instance().globalIndent;
            GlobalIndent::instance().globalIndent += "\t";
            for (int j = 0; j < 4; j++)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "Decrement currentExpressionAddressOffset\n";
                GlobalVariableBindings::instance().decrementCurrentGlobalExpressionAddressOffset();
                std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
                out << Mips::load_word(j + 4, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
            }
            GlobalIndent::instance().globalIndent = oldGlobalIndent;
        }

        out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
    }

    std::cerr << GlobalIndent::instance().globalIndent << "FnCall::print\tEND\n";
};