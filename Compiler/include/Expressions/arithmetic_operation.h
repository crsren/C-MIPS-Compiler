#ifndef ARITHMETIC_OPERATION_H
#define ARITHMETIC_OPERATION_H

#include "../helpers.h"
#include "binary_operation.h"

#include <string>

class ArithmeticOperation : public BinaryOperation
{
public:
    // constructor inherited from BinaryOperation
    ArithmeticOperation(nodePtr l, const std::string &s, nodePtr r) : BinaryOperation(l, s, r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "ArithmeticOperation::print\tSTART\n";
        
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
            switch (operationSymbol[0])
            {
            case '+':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'+' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::addu(2, 2, 3);
                break;

            case '-':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'-' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::subu(2, 2, 3);
                break;

            case '*':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'*' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::mul(2, 2, 3);
                break;

            case '/':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'/' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::div_quotient(2, 2, 3);
                break;

            case '%':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'%' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::div_remainder(2, 2, 3);
                break;
            }

            std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
            out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
        }

        else
        {
            std::cerr << GlobalIndent::instance().globalIndent << "Get the currentGlobalExpressionAddressOffset:" << std::to_string(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset()) << "\n";
            int originalExpressionAddressOffset = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print LHS\n";
            left->print(out, bindings);

            std::cerr << GlobalIndent::instance().globalIndent << "Get the leftGlobalExpressionAddressOffset\n";
            int leftGlobalExpressionAddressOffset = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentGlobalExpressionAddressOffset\n";
            GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print RHS\n";
            right->print(out, bindings);

            std::cerr << GlobalIndent::instance().globalIndent << "Get the rightGlobalExpressionAddressOffset\n";
            int rightGlobalExpressionAddressOffset = GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentGlobalExpressionAddressOffset\n";
            GlobalVariableBindings::instance().incrementCurrentGlobalExpressionAddressOffset();

            std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
            out << Mips::load_word(2, leftGlobalExpressionAddressOffset, false);
            out << Mips::load_word(3, rightGlobalExpressionAddressOffset, false);

            std::cerr << GlobalIndent::instance().globalIndent << "Decrement the currentGlobalExpressionAddressOffset by"<< std::to_string(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() - leftGlobalExpressionAddressOffset) << "\n";
            GlobalVariableBindings::instance().decrementCurrentGlobalExpressionAddressOffsetBy(GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset() - originalExpressionAddressOffset);

            std::cerr << GlobalIndent::instance().globalIndent << "Switch Statement - Checking the operation symbol\n";
            switch (operationSymbol[0])
            {
            case '+':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'+' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::addu(2, 2, 3);
                break;

            case '-':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'-' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::subu(2, 2, 3);
                break;

            case '*':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'*' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::mul(2, 2, 3);
                break;

            case '/':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'/' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::div_quotient(2, 2, 3);
                break;

            case '%':
                std::cerr << GlobalIndent::instance().globalIndent << "\t'%' operation symbol\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::div_remainder(2, 2, 3);
                break;
            }

            std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
            out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
        }

        std::cerr << GlobalIndent::instance().globalIndent << "ArithmeticOperation::print\tEND\n";
    }
};

#endif // BINARY_OPERATION_H
