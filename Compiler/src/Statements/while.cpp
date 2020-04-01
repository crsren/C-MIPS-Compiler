#include "Statements/while.h"

void WhileStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    // No need to enter scope as this is done in the compound statement
    std::cerr << "WhileStatement::print\tSTART\n";

    std::cerr << "Getting the WHILE and DO labels\n";
    std::string WHILE = Label::instance().uniquify("while_c");
    std::string DO = Label::instance().uniquify("while_do");

    //TODO: Add loop labels to bindings

    // CHECK if break is needed
    std::cerr << "Print MIPS code\n";
    out << Mips::branch(WHILE);

    out << Mips::new_label(DO);

    std::cerr << "Print the while compound statement\n";
    statement->print(out, bindings);

    std::cerr << "\t\tPrint MIPS code\n";
    out << Mips::new_label(WHILE);

    std::cerr << "Print the while condition expression\n";
    condition->print(out, bindings);

    std::cerr << "\t\tPrint MIPS code\n";
    out << Mips::bne(0, 2, DO);

    //CHECK: need break label?
    //TODO: Pop loop labels from bindings

    std::cerr << "WhileStatement::print\tEND\n";
}
