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
        std::cerr << "ArithmeticOperation::print\tSTART\n";
        std::cerr << "Print LHS\n";
        left->print(out, bindings);

        std::cerr << "Get the currentExpressionAddressOffset\n";
        int leftExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

        std::cerr << "Increment the currentExpressionAddressOffset\n";
        bindings->incrementCurrentExpressionAddressOffset();

        std::cerr << "Print RHS\n";
        right->print(out, bindings);

        std::cerr << "Print MIPS code\n";
        out << Mips::load_word(2, leftExpressionAddressOffset, false);
        out << Mips::load_word(3, bindings->getCurrentExpressionAddressOffset(), false);
        
        std::cerr << "Decrement the currentExpressionAddressOffset by"<< std::to_string(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset) << "\n";
        bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);
        
        std::cerr << "Switch Statement - Checking the operation symbol\n";
        switch (operationSymbol[0])
        {
        case '+':
            std::cerr << "\t'+' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::addu(2, 2, 3);
            break;

        case '-':
            std::cerr << "\t'-' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::subu(2, 2, 3);
            break;

        case '*':
            std::cerr << "\t'*' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::mul(2, 2, 3);
            break;

        case '/':
            std::cerr << "\t'/' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::div_quotient(2, 2, 3);
            break;

        case '%':
            std::cerr << "\t'%' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::div_remainder(2, 2, 3);
            break;
        }

        std::cerr << "Print MIPS code\n";
        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
        std::cerr << "ArithmeticOperation::print\tEND\n";
    }
};

#endif // BINARY_OPERATION_H
