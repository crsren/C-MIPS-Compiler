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
        std::cerr << "BitwiseOperation::print\tSTART\n";
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
        if (operationSymbol == "^")
        {
            std::cerr << "\t'^' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::xor_(2, 2, 3);
        }
        else if (operationSymbol == "&")
        {
            std::cerr << "\t'&' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::and_(2, 2, 3);
        }
        else if (operationSymbol == "|")
        {
            std::cerr << "\t'|' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::or_(2, 2, 3);
        }
        else if (operationSymbol == "<<")
        {
            std::cerr << "\t'<<' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::sll(2, 2, 3);
        }
        else if (operationSymbol == ">>")
        {
            std::cerr << "\t'>>' operation symbol\n";
            std::cerr << "\tPrint MIPS code\n";
            out << Mips::sra(2, 2, 3);
        }

        std::cerr << "Print MIPS code\n";
        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);

        std::cerr << "BitwiseOperation::print\tEND\n";
    }
};

#endif // BITWISE_OPERATION_H
