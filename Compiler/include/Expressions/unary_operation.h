#ifndef UNARY_OPERATION_H
#define UNARY_OPERATION_H

#include "../helpers.h"

// '&' '*' '+' '-' '~' '!'
class UnaryOperation : public Node
{
private:
    const unsigned char operationSymbol;
    nodePtr postfixExpression;

public:
    UnaryOperation(unsigned char s, nodePtr uExp) : operationSymbol(s), postfixExpression(uExp){};

    ~UnaryOperation()
    {
        delete postfixExpression;
    }

    void print(std::ostream &out, LocalVariableBindings bindings) const override
    {
        postfixExpression -> print(out, bindings);
        
        out << Mips::load_word(2, bindings.getCurrentExpressionAddressOffset(), false);

        int operationSymbolNumber;
        if(operationSymbol == '+')
        {
            operationSymbolNumber = 0;
        }
        else if(operationSymbol == '-')
        {
            operationSymbolNumber = 1;
        }
        else if(operationSymbol == '~')
        {
            operationSymbolNumber = 2;
        }
        else if(operationSymbol == '!')
        {
            operationSymbolNumber = 3;
        }
        // else if(operationSymbol == '&')
        // {
        //     operationSymbolNumber = 4;
        // }
        // else if(operationSymbol == '*')
        // {
        //     operationSymbolNumber = 5;
        // }

        switch(operationSymbolNumber)
        {
            case 0: break;

            case 1: out << Mips::sub_(2, 0, 2);
                    break;

            case 2: out << Mips::nor_(2, 0, 2);
                    break;

            case 3: std::string ELSE = Label::instance().uniquify("else");
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
