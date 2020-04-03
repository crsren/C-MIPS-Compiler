#include "Statements/while.h"

void WhileStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    // No need to enter scope as this is done in the compound statement
    std::cerr << GlobalIndent::instance().globalIndent << "WhileStatement::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Getting the WHILE and DO labels\n";
    std::string WHILE = Label::instance().uniquify("while_c");
    std::string DO = Label::instance().uniquify("while_do");
    std::string END = Label::instance().uniquify("while_end");

    // Adding loop labels to bindings (for break, continue)
    bindings->push_startLabel(WHILE);
    bindings->push_endLabel(END);

    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::new_label(WHILE);

    std::cerr << GlobalIndent::instance().globalIndent << "Print the while condition expression\n";
    condition->print(out, bindings);

    std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrint MIPS code\n";
    out << Mips::beq(0, 2, END);

    out << Mips::new_label(DO);

    std::cerr << GlobalIndent::instance().globalIndent << "Print the while compound statement\n";
    if (statement)
        statement->print(out, bindings);
    out << Mips::branch(WHILE);

    std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrint MIPS code\n";

    out << Mips::new_label(END);

    bindings->pop_startLabel();
    bindings->pop_endLabel();

    std::cerr << GlobalIndent::instance().globalIndent << "WhileStatement::print\tEND\n";
}
