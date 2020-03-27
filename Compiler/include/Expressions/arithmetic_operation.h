#ifndef BINARY_OPERATION_H
#define BIANRY_OPERATION_H

#include "helpers.h"
#include "../node.h"
#include "../Context/bindings.h"

#include <string>

class ArithmeticOperation : public Node
{
private:
    nodePtr left;
    const std::string symbol;
    nodePtr right;

public:
    ArithmeticOperation(nodePtr l, const std::string &s, nodePtr r) : left(l), symbol(s), right(r){};

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        left -> print(out, bindings);
        int leftExpressionAddressOffset = bindings.getCurrentExpressionAddressOffset();

        bindings.incrementCurrentExpressionAddressOffset();
        right -> print(out, bindings);

        out << "\tlw\t$2,-" << leftExpressionAddressOffset << "($fp)\n";
        out << "\tlw\t$3,-" << bindings.getCurrentExpressionAddressOffset() << "($fp)\n";

        bindings.decrementCurrentExpressionAddressOffsetBy(bindings.getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);

        int symbolNumber;
        if(symbol == "+")
        {
            symbolNumber = 0;
        }
        else if(symbol == "-")
        {
            symbolNumber = 1;
        }
        else if(symbol == "*")
        {
            symbolNumber = 2;
        }
        else if(symbol == "/")
        {
            symbolNumber = 3;
        }
        else if(symbol == "%")
        {
            symbolNumber = 4;
        }

        switch(symbolNumber)
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

#endif // BINARY_OPERATION_H
