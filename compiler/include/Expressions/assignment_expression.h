#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include "../helpers.h"
#include "Expressions/primitives.h"

#include <string>

class AssignmentExpression : public Node
{
private:
    nodePtr left;
    nodePtr right;

public:
    //simple "=", possible associated binary operation has been daelt with in parser
    AssignmentExpression(Node *l, Node *r) : left(l), right(r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        int rhsExpressionStackPointer = bindings->getCurrentExpressionAddressOffset();

        right->print(out, bindings);

        nodePtr left;
        const Identifier *identifierPtr = dynamic_cast<const Identifier *>(left);
        if (identifierPtr == nullptr)
            std::cerr << "Left side of assignment could not be casted to an identifier.\n";

        const std::string identifierName = identifierPtr->getName();

        out << Mips::load_word(2, rhsExpressionStackPointer, false);

        out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifierName), false);

        bindings->decrementCurrentExpressionAddressOffsetBy(bindings->getCurrentExpressionAddressOffset() - rhsExpressionStackPointer);
    }
};

#endif // ASSIGNMENT_H
