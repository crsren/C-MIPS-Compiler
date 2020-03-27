#ifndef ARITHMETIC_OPERATION_H
#define ARITHMETIC_OPERATION_H

#include "../helpers.h"
#include "binary_operation.h"

#include <string>

class ArithmeticOperation : public BinaryOperation
{
public:
    ArithmeticOperation(nodePtr l, const std::string &s, nodePtr r) : BinaryOperation(l, s, r){};

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        left -> print(out, bindings);
        int leftExpressionAddressOffset = bindings.getCurrentExpressionAddressOffset();

        bindings.incrementCurrentExpressionAddressOffset();
        right -> print(out, bindings);

        out << Mips::load_word(2, leftExpressionAddressOffset, false);
        out << Mips::load_word(3, bindings.getCurrentExpressionAddressOffset(), false);

        bindings.decrementCurrentExpressionAddressOffsetBy(bindings.getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);

        int operationSymbolNumber;
        if(operationSymbol == "+")
        {
            operationSymbolNumber = 0;
        }
        else if(operationSymbol == "-")
        {
            operationSymbolNumber = 1;
        }
        else if(operationSymbol == "*")
        {
            operationSymbolNumber = 2;
        }
        else if(operationSymbol == "/")
        {
            operationSymbolNumber = 3;
        }
        else if(operationSymbol == "%")
        {
            operationSymbolNumber = 4;
        }

        switch(operationSymbolNumber)
        {
            case 0: out << Mips::addu(2, 2, 3);
                    break;

            case 1: out << Mips::subu(2, 2, 3);
                    break;

            case 2: out << Mips::mul(2, 2, 3);
                    break;

            case 3: out << Mips::div_quotient(2, 2, 3);
                    break;
            
            case 4: out << Mips::div_remainder(2, 2, 3);
                    break;
        }

        out << Mips::store_word(2, bindings.getCurrentExpressionAddressOffset(), false);
    }

};

#endif // BINARY_OPERATION_H
