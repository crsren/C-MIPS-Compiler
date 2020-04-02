#ifndef BOOLEAN_OPERATION_H
#define BOOLEAN_OPERATION_H

#include "binary_operation.h"
#include "../helpers.h"

// <, >, <=, >=, ==, !=
class BooleanOperation : public BinaryOperation
{
public:
    BooleanOperation(nodePtr l, const std::string &s, nodePtr r) : BinaryOperation(l, s, r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "BooleanOperation::print\tSTART\n";
        std::cerr << GlobalIndent::instance().globalIndent << "Print LHS\n";
        left->print(out, bindings);

        std::cerr << GlobalIndent::instance().globalIndent << "Get the currentExpressionAddressOffset\n";
        int leftExpressionAddressOffset = bindings->getCurrentExpressionAddressOffset();

        std::cerr << GlobalIndent::instance().globalIndent << "Increment the currentExpressionAddressOffset\n";
        bindings->incrementCurrentExpressionAddressOffset();

        std::cerr << GlobalIndent::instance().globalIndent << "Print RHS\n";
        right->print(out, bindings);

        std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
        out << Mips::load_word(2, leftExpressionAddressOffset, false);
        out << Mips::load_word(3, bindings->getCurrentExpressionAddressOffset(), false);

        std::cerr << GlobalIndent::instance().globalIndent << "Decrement the currentExpressionAddressOffset by"<< std::to_string(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset) << "\n";
        bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - leftExpressionAddressOffset);

        int operationSymbolNumber;
        if (operationSymbol == "<")
        {
            operationSymbolNumber = 0;
        }
        else if (operationSymbol == ">")
        {
            operationSymbolNumber = 1;
        }
        else if (operationSymbol == "<=")
        {
            operationSymbolNumber = 2;
        }
        else if (operationSymbol == ">=")
        {
            operationSymbolNumber = 3;
        }
        else if (operationSymbol == "==")
        {
            operationSymbolNumber = 4;
        }
        else if (operationSymbol == "!=")
        {
            operationSymbolNumber = 5;
        }

        std::cerr << GlobalIndent::instance().globalIndent << "Switch Statement - Checking the operation symbol\n";
        switch (operationSymbolNumber)
        {
        case 0:
            std::cerr << GlobalIndent::instance().globalIndent << "\t'<' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::slt(2, 2, 3);
            break;

        case 1:
            std::cerr << GlobalIndent::instance().globalIndent << "\t'>' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::slt(2, 3, 2);
            break;

        case 2:
            std::cerr << GlobalIndent::instance().globalIndent << "\t'<=' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::slt(2, 3, 2);
            out << Mips::xori(2, 2, 1);
            break;

        case 3:
            std::cerr << GlobalIndent::instance().globalIndent << "\t'>=' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::slt(2, 2, 3);
            out << Mips::xori(2, 2, 1);
            break;

        case 4:
            std::cerr << GlobalIndent::instance().globalIndent << "\t'==' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::xor_(2, 2, 3);
            out << Mips::sltiu(2, 2, 1);
            break;

        case 5:
            std::cerr << GlobalIndent::instance().globalIndent << "\t'!=' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::xor_(2, 2, 3);
            out << Mips::sltu(2, 0, 2);
            break;
        }

        std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
        out << Mips::andi(2, 2, 255);
        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset() - 4, false);

        std::cerr << GlobalIndent::instance().globalIndent << "BooleanOperation::print\tEND\n";
    }
};

#endif // BOOL_OPERATION_H
