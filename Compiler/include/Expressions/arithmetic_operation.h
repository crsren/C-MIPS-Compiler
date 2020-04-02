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
        std::cerr << GlobalIndent::instance().globalIndent << "Print LHS\n";
        left->print(out, bindings);

        std::cerr << GlobalIndent::instance().globalIndent << "Get the currentExpressionAddressOffset\n";
        int leftExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

        std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentExpressionAddressOffset\n";
        bindings->incrementCurrentExpressionAddressOffset();

        std::cerr << GlobalIndent::instance().globalIndent << "Print RHS\n";
        right->print(out, bindings);

        std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentExpressionAddressOffset\n";
        bindings->incrementCurrentExpressionAddressOffset();

        std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
        out << Mips::load_word(2, leftExpressionAddressOffset, false);
        out << Mips::load_word(3, bindings->getCurrentExpressionAddressOffset() - 4, false);
        
        std::cerr << GlobalIndent::instance().globalIndent << "Decrement the currentExpressionAddressOffset by"<< std::to_string(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset) << "\n";
        bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);
        
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
        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset() - 4, false);
        std::cerr << GlobalIndent::instance().globalIndent << "ArithmeticOperation::print\tEND\n";
    }
};

#endif // BINARY_OPERATION_H
