#include "Statements/for.h"

void ForStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << "ForStatement::print\tSTART\n";

    std::cerr << "Getting the FOR and DO labels\n";
    std::string FOR = Label::instance().uniquify("for_c");
    std::string DO = Label::instance().uniquify("for_do");

    //TODO: Add loop labels to bindings

    std::cerr << "Print the initializing loop counter assignment expression\n";
    init->print(out, bindings); // int i = 0;
    
    std::cerr << "Print MIPS code\n";
    out << Mips::branch(FOR);

    out << Mips::new_label(DO);
    std::cerr << "Print the loop compound statement\n";
    statement->print(out, bindings);

    std::cerr << "Print the loop counter incrementation expression\n";
    alteration->print(out, bindings); // i++

    std::cerr << "Print MIPS code\n";
    out << Mips::new_label(FOR);

    std::cerr << "Print the loop counter condition\n";
    condition->print(out, bindings); // i < x
    std::cerr << "Print MIPS code\n";
    out << Mips::bne(0, 2, DO);

    std::cerr << "ForStatement::print\tEND\n";
    //CHECK: need break label?
    //TODO: Pop loop labels from bindings
}