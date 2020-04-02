#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include "../helpers.h"
#include "../Expressions/primitives.h"

#include <string>

class AssignmentExpression : public Node
{
private:
    nodePtr left;
    nodePtr right;

public:
    //simple "=", possible associated binary operation has been dealt with in parser
    AssignmentExpression(nodePtr l, nodePtr r) : left(l), right(r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "AssignmentExpression::print\tSTART\n";

        std::cerr << GlobalIndent::instance().globalIndent << "Get the currentExpressionAddressOffset\n";
        int rhsExpressionStackPointer = bindings->getCurrentExpressionAddressOffset();

        std::cerr << GlobalIndent::instance().globalIndent << "Print RHS\n";
        right->print(out, bindings);

        nodePtr left;
        std::cerr << GlobalIndent::instance().globalIndent << "Cast LHS to a pointer to an Identifier\n";
        const Identifier *identifierPtr = dynamic_cast<const Identifier *>(left);
        if (identifierPtr == nullptr)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the LHS cannot be casted to an Identifier)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tThat is not supported yet\n";
        }

        std::cerr << GlobalIndent::instance().globalIndent << "Getting the identifier name\n";
        const std::string identifierName = identifierPtr->getName();

        std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
        out << Mips::load_word(2, rhsExpressionStackPointer, false);

        out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifierName), false);

        std::cerr << GlobalIndent::instance().globalIndent << "Decrement the currentExpressionAddressOffset by"<< std::to_string(bindings->getCurrentExpressionAddressOffset() - rhsExpressionStackPointer) << "\n";
        bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - rhsExpressionStackPointer);
        
        std::cerr << GlobalIndent::instance().globalIndent << "AssignmentExpression::print\tEND\n";
    }
};

#endif // ASSIGNMENT_H
