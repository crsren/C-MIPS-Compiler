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

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        left -> print(out, bindings);
        int leftExpressionAddressOffset = bindings.getCurrentExpressionAddressOffset();

        bindings.incrementCurrentExpressionAddressOffset();
        right -> print(out, bindings);

        out << "\tlw\t$2,-" << leftExpressionAddressOffset << "($fp)\n";
        out << "\tlw\t$3,-" << bindings.getCurrentExpressionAddressOffset() << "($fp)\n";

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
            case 0: out << "\taddu\t$2,$2,$3\n";
                    break;

            case 1: out << "\tsubu\t$2,$2,$3\n";
                    break;

            case 2: out << "\tmul\t$2,$2,$3\n";
                    break;

            case 3: out << "\tdiv\t$2,$3\n" << "\tmflo\t$2\n";
                    break;
            
            case 4: out << "\tdiv\t$2,$3\n" << "\tmfhi\t$2\n";
                    break;
        }

        out << "\tsw\t$2,-" << bindings.getCurrentExpressionAddressOffset() << "($fp)\n";
    }
};

#endif // BITWISE_OPERATION_H
