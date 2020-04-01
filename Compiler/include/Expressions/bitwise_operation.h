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
        left->print(out, bindings);
        int leftExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

        bindings->incrementCurrentExpressionAddressOffset();
        right->print(out, bindings);

        out << Mips::load_word(2, leftExpressionAddressOffset, false);
        out << Mips::load_word(3, bindings->getCurrentExpressionAddressOffset(), false);

        bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);

        if (operationSymbol == "^")
        {
            out << Mips::xor_(2, 2, 3);
        }
        else if (operationSymbol == "&")
        {
            out << Mips::and_(2, 2, 3);
        }
        else if (operationSymbol == "|")
        {
            out << Mips::or_(2, 2, 3);
        }
        else if (operationSymbol == "<<")
        {
            out << Mips::sll(2, 2, 3);
        }
        else if (operationSymbol == ">>")
        {
            out << Mips::sra(2, 2, 3);
        }

        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
    }
};

#endif // BITWISE_OPERATION_H
