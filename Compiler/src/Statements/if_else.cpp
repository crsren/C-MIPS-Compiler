#include "Statements/if_else.h"

void IfElseStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    // No need to enter scope as this is done in the compound statement
    std::cerr << "IfElseStatement::print\tSTART\n";

    std::cerr << "Getting the ELSE and END labels\n";
    std::string ELSE = Label::instance().uniquify("else");
    std::string END = Label::instance().uniquify("fi");

    std::cerr << "Print the if condition\n";
    condition->print(out, bindings);

    std::cerr << "Print MIPS code\n";
    out << Mips::beq(0, 2, ELSE); //if false, jump to else

    std::cerr << "Print the if compound statement\n";
    statement1->print(out, bindings); // if statement

    std::cerr << "Print MIPS code\n";
    out << Mips::branch(END);

    out << Mips::new_label(ELSE);

    if (has_else)
    {
        std::cerr << "if (the if_else statement has an else)\n";
        std::cerr << "\tPrint the else compound statement\n";
        statement2->print(out, bindings);

    }

    std::cerr << "Print MIPS code\n";
    out << Mips::new_label(END);

    std::cerr << "IfElseStatement::print\tEND\n";
};