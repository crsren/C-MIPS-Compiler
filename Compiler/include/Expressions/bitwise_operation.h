#ifndef BITWISE_OPERATION_H
#define BITWISE_OPERATION_H

#include "binary_operation.h"
#include "../helpers.h"

// bitwise operations:
//  ^, &, |, <<, >>
class BitwiseOperation : public BinaryOperation
{
public:
    BitwiseOperation(nodePtr l, const std::string &s, nodePtr r) : BinaryOperation(l, s, r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "BitwiseOperation::print\tSTART\n";

        if (bindings)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "Get the currentExpressionAddressOffset:" << std::to_string(bindings->getCurrentExpressionAddressOffset()) << "\n";
            int originalExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print LHS\n";
            left->print(out, bindings);

            std::cerr << GlobalIndent::instance().globalIndent << "Get the leftExpressionAddressOffset\n";
            int leftExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentExpressionAddressOffset\n";
            bindings->incrementCurrentExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print RHS\n";
            right->print(out, bindings);

            std::cerr << GlobalIndent::instance().globalIndent << "Get the rightExpressionAddressOffset\n";
            int rightExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentExpressionAddressOffset\n";
            bindings->incrementCurrentExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
            out << Mips::load_word(2, leftExpressionAddressOffset, false);
            out << Mips::load_word(3, rightExpressionAddressOffset, false);

            std::cerr << GlobalIndent::instance().globalIndent << "Decrement the currentExpressionAddressOffset by"<< std::to_string(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset) << "\n";
            bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - originalExpressionAddressOffset);

            std::cerr << GlobalIndent::instance().globalIndent << "Switch Statement - Checking the operation symbol\n";
            if (operationSymbol == "^")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'^' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::xor_(2, 2, 3);
            }
            else if (operationSymbol == "&")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'&' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::and_(2, 2, 3);
            }
            else if (operationSymbol == "|")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'|' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::or_(2, 2, 3);
            }
            else if (operationSymbol == "<<")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'<<' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::sllv(2, 2, 3);
            }
            else if (operationSymbol == ">>")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'>>' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::srav(2, 2, 3);
            }

            std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
            out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
        }

        else
        {
            std::cerr << GlobalIndent::instance().globalIndent << "Get the currentGlobalExpressionAddressOffset:" << std::to_string(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset()) << "\n";
            int originalGlobalExpressionAddressOffset = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print LHS\n";
            left->print(out, bindings);

            std::cerr << GlobalIndent::instance().globalIndent << "Get the leftGlobalExpressionAddressOffset\n";
            int leftGlobalExpressionAddressOffset = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentGlobalExpressionAddressOffset\n";
            GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print RHS\n";
            right->print(out, bindings);

            std::cerr << GlobalIndent::instance().globalIndent << "Get the rightExpressionAddressOffset\n";
            int rightExpressionAddressOffset = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentGlobalExpressionAddressOffset\n";
            GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
            out << Mips::load_word(2, leftGlobalExpressionAddressOffset, false);
            out << Mips::load_word(3, rightExpressionAddressOffset, false);

            std::cerr << GlobalIndent::instance().globalIndent << "Decrement the currentGlobalExpressionAddressOffset by"<< std::to_string(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() - leftGlobalExpressionAddressOffset) << "\n";
            GlobalVariableBindings::instance().decrementCurrentGlobalExpressionAddressOffsetBy(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() - originalGlobalExpressionAddressOffset);

            std::cerr << GlobalIndent::instance().globalIndent << "Switch Statement - Checking the operation symbol\n";
            if (operationSymbol == "^")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'^' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::xor_(2, 2, 3);
            }
            else if (operationSymbol == "&")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'&' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::and_(2, 2, 3);
            }
            else if (operationSymbol == "|")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'|' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::or_(2, 2, 3);
            }
            else if (operationSymbol == "<<")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'<<' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::sllv(2, 2, 3);
            }
            else if (operationSymbol == ">>")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t'>>' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::srav(2, 2, 3);
            }

            std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
            out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
        }

        std::cerr << GlobalIndent::instance().globalIndent << "BitwiseOperation::print\tEND\n";
    }
};

#endif // BITWISE_OPERATION_H
