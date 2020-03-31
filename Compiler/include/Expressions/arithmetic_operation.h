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
        left->print(out, bindings);
        int leftExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

        bindings->incrementCurrentExpressionAddressOffset();
        right->print(out, bindings);

        out << Mips::load_word(2, leftExpressionAddressOffset, false);
        out << Mips::load_word(3, bindings->getCurrentExpressionAddressOffset(), false);

        bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);

        switch (operationSymbol[0])
        {
        case '+':
            out << Mips::addu(2, 2, 3);
            break;

        case '-':
            out << Mips::subu(2, 2, 3);
            break;

        case '*':
            out << Mips::mul(2, 2, 3);
            break;

        case '/':
            out << Mips::div_quotient(2, 2, 3);
            break;

        case '%':
            out << Mips::div_remainder(2, 2, 3);
            break;
        }

        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
    }
};

#endif // BINARY_OPERATION_H
