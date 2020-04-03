#include "Expressions/unary_operation.h"

void UnaryOperation::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "UnaryOperation::print\tSTART\n";

    if (bindings)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "Print postfix expression\n";
        postfixExpression->print(out, bindings);

        std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
        out << Mips::load_word(2, bindings->getCurrentExpressionAddressOffset(), false);

        std::cerr << GlobalIndent::instance().globalIndent << "Switch Statement - Checking the operation symbol\n";
        switch (operationSymbol[0])
        {
        case '+':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'+' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tDO NOTHING\n";
            break;

        case '-':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'-' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::sub_(2, 0, 2);
            break;

        case '~':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'~' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::nor_(2, 0, 2);
            break;

        case '!':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'!' operation symbol\n";

            std::cerr << GlobalIndent::instance().globalIndent << "\tCreate ELSE and END labels\n";
            std::string ELSE = Label::instance().uniquify("else");
            std::string END = Label::instance().uniquify("fi");

            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
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

        std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
        out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
    }

    else
    {
        std::cerr << GlobalIndent::instance().globalIndent << "Print postfix expression\n";
        postfixExpression->print(out, bindings);

        std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
        out << Mips::load_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);

        std::cerr << GlobalIndent::instance().globalIndent << "Switch Statement - Checking the operation symbol\n";
        switch (operationSymbol[0])
        {
        case '+':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'+' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tDO NOTHING\n";
            break;

        case '-':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'-' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::sub_(2, 0, 2);
            break;

        case '~':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'~' operation symbol\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::nor_(2, 0, 2);
            break;

        case '!':
            std::cerr << GlobalIndent::instance().globalIndent << "\t'!' operation symbol\n";

            std::cerr << GlobalIndent::instance().globalIndent << "\tCreate ELSE and END labels\n";
            std::string ELSE = Label::instance().uniquify("else");
            std::string END = Label::instance().uniquify("fi");

            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
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

        std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
        out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
    }

    std::cerr << GlobalIndent::instance().globalIndent << "UnaryOperation::print\tEND\n";
}

void PreOperation::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    expression->print(out, bindings); // evaluate unary expression

    const Identifier * cast_identifier = dynamic_cast<const Identifier *>(expression);
    // if nodePtr is not a Identifier* -> returns nullptr
    // if Identifier* and nodePtr arent "related" -> returns nullptr
    if (cast_identifier == nullptr)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "Error: you are not supposed to have a pre-operation symbol:" << symbol << " and after a non-variable expression\n";
    }

    std::string identifier = cast_identifier->getName();

    // alter then store unary expression
    switch (symbol)
    {
    case '+':
        out << Mips::addiu(2, 2, 1);
        out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
        break;

    case '-':
        out << Mips::addiu(2, 2, -1);
        out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
        break;
    }

    // Check
    out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
}

void PostOperation::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    expression->print(out, bindings); // evaluate postfix expression

    const Identifier * cast_identifier = dynamic_cast<const Identifier *>(expression);
    // if nodePtr is not a Identifier* -> returns nullptr
    // if Identifier* and nodePtr arent "related" -> returns nullptr
    if (cast_identifier == nullptr)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "Error: you are not supposed to have a pre-operation symbol:" << symbol << " and after a non-variable expression\n";
    }

    std::string identifier = cast_identifier->getName();

    switch (symbol)
    {
    case '+':
        out << Mips::addiu(8, 2, 1);
        out << Mips::store_word(8, bindings->getLocalVariableAddressOffset(identifier), false);
        break;

    case '-':
        out << Mips::addiu(8, 2, -1);
        out << Mips::store_word(8, bindings->getLocalVariableAddressOffset(identifier), false);
        break;
    }

    // Check
    out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
}