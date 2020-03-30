#ifndef BOOLEAN_OPERATION_H
#define BOOLEAN_OPERATION_H

#include "binary_operation.h"
#include "../helpers.h"

// <, >, <=, >=, ==, !=
class BooleanOperation : public BinaryOperation
{
public:
    BooleanOperation(nodePtr l, const std::string &s, nodePtr r) : BinaryOperation(l, s, r){};

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
        if(operationSymbol == "<")
        {
            operationSymbolNumber = 0;
        }
        else if(operationSymbol == ">")
        {
            operationSymbolNumber = 1;
        }
        else if(operationSymbol == "<=")
        {
            operationSymbolNumber = 2;
        }
        else if(operationSymbol == ">=")
        {
            operationSymbolNumber = 3;
        }
        else if(operationSymbol == "==")
        {
            operationSymbolNumber = 4;
        }
        else if(operationSymbol == "!=")
        {
            operationSymbolNumber = 5;
        }

        switch(operationSymbolNumber)
        {
            case 0: out << Mips::slt(2, 2, 3);
                    break;

            case 1: out << Mips::slt(2, 3, 2);
                    break;

            case 2: out << Mips::slt(2, 3, 2);
                    out << Mips::xori(2, 2, 1);
                    break;

            case 3: out << Mips::slt(2, 2, 3);
                    out << Mips::xori(2, 2, 1);
                    break;
            
            case 4: out << Mips::xor_(2, 2, 3);
                    out << Mips::sltiu(2, 2, 1);
                    break;
            
            case 5: out << Mips::xor_(2, 2, 3);
                    out << Mips::sltu(2, 0, 2);
                    break;
        }

        out << Mips::andi(2, 2, 255);
        out << Mips::store_word(2, bindings.getCurrentExpressionAddressOffset(), false);
    }
};

#endif // BOOL_OPERATION_H
