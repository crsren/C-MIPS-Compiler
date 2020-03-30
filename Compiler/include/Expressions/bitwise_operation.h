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

    void print(std::ostream &out, LocalVariableBindings bindings) const override
    {
        left -> print(out, bindings);
        int leftExpressionAddressOffset = bindings.getCurrentExpressionAddressOffset();

        bindings.incrementCurrentExpressionAddressOffset();
        right -> print(out, bindings);

        out << Mips::load_word(2, leftExpressionAddressOffset, false);
        out << Mips::load_word(3, bindings.getCurrentExpressionAddressOffset(), false);

        bindings.decrementCurrentExpressionAddressOffsetBy(bindings.getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);

        int operationSymbolNumber;
        if(operationSymbol == "^")
        {
            operationSymbolNumber = 0;
        }
        else if(operationSymbol == "&")
        {
            operationSymbolNumber = 1;
        }
        else if(operationSymbol == "|")
        {
            operationSymbolNumber = 2;
        }
        else if(operationSymbol == "<<")
        {
            operationSymbolNumber = 3;
        }
        else if(operationSymbol == ">>")
        {
            operationSymbolNumber = 4;
        }

        switch(operationSymbolNumber)
        {
            case 0: out << Mips::xor_(2, 2, 3);
                    break;

            case 1: out << Mips::and_(2, 2, 3);
                    break;

            case 2: out << Mips::or_(2, 2, 3);
                    break;

            case 3: out << Mips::sll(2, 2, 3);
                    break;
            
            case 4: out << Mips::sra(2, 2, 3);
                    break;
        }

        out << Mips::store_word(2, bindings.getCurrentExpressionAddressOffset(), false);
    }
};

#endif // BITWISE_OPERATION_H
