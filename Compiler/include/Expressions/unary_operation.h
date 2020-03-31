#ifndef UNARY_OPERATION_H
#define UNARY_OPERATION_H

#include "../helpers.h"

// '&' '*' '+' '-' '~' '!'
class UnaryOperation : public Node
{
private:
    const std::string operationSymbol;
    nodePtr postfixExpression;

public:
    UnaryOperation(std::string s, nodePtr uExp) : operationSymbol(s), postfixExpression(uExp){};

    ~UnaryOperation()
    {
        delete postfixExpression;
    }

    void print(std::ostream &out, LocalVariableBindings &bindings) const override
    {
        postfixExpression->print(out, bindings);

        out << Mips::load_word(2, bindings.getCurrentExpressionAddressOffset(), false);

        switch (operationSymbol[0])
        {
        case '+':
            break;

        case '-':
            out << Mips::sub_(2, 0, 2);
            break;

        case '~':
            out << Mips::nor_(2, 0, 2);
            break;

        case '!':
            std::string ELSE = Label::instance().uniquify("else");
            std::string END = Label::instance().uniquify("fi");

            out << Mips::beq(0, 2, ELSE); // if $2 is equal to zero

            out << Mips::move(2, 0); // assign $2 to 0x0

            out << Mips::branch(END);

            out << Mips::new_label(ELSE);

            out << Mips::addi(2, 0, 1); // assign $2 to 0x1

            out << Mips::new_label(END);
            break;

            // case 4: out << Mips::xor_(2, 2, 3);
            //         out << Mips::sltiu(2, 2, 1);
            //         break;

            // case 5: out << Mips::xor_(2, 2, 3);
            //         out << Mips::sltu(2, 0, 2);
            //         break;
        }

        out << Mips::store_word(2, bindings.getCurrentExpressionAddressOffset(), false);
    }
};

/// Later:
// class preOperation: ++n, --n
//c lass postOperation: n++, n--

#endif // UNARY_OPERATION_H
