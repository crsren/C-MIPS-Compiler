#include "Statements/for.h"

void ForStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "ForStatement::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Getting the FOR and DO labels\n";
    std::string FOR = Label::instance().uniquify("for_c");
    std::string DO = Label::instance().uniquify("for_do");

    //TODO: Add loop labels to bindings

    std::cerr << GlobalIndent::instance().globalIndent << "Print the initializing loop counter assignment expression\n";
    init->print(out, bindings); // int i = 0;
    
    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::branch(FOR);

    out << Mips::new_label(DO);
    std::cerr << GlobalIndent::instance().globalIndent << "Print the loop compound statement\n";
    statement->print(out, bindings);

    std::cerr << GlobalIndent::instance().globalIndent << "Print the loop counter incrementation expression\n";
    alteration->print(out, bindings); // i++

    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::new_label(FOR);

    std::cerr << GlobalIndent::instance().globalIndent << "Print the loop counter condition\n";
    condition->print(out, bindings); // i < x
    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::bne(0, 2, DO);

    std::cerr << GlobalIndent::instance().globalIndent << "ForStatement::print\tEND\n";
    //CHECK: need break label?
    //TODO: Pop loop labels from bindings
}