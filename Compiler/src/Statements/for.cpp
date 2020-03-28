#include "Statements/for.h"

void ForStatement::print(std::ostream &out, VariableBindings &bindings) const
{
    std::string FOR = Label::instance().uniquify("for_c");
    std::string DO = Label::instance().uniquify("for_do");

    //TODO: Add loop labels to bindings

    init->print(out, bindings); // int i = 0;
    out << Mips::branch(FOR);

    out << Mips::new_label(DO);
    statement->print(out, bindings);
    alteration->print(out, bindings); // i++

    out << Mips::new_label(FOR);
    condition->print(out, bindings); // i < x
    out << Mips::bne(0, 2, DO);

    //CHECK: need break label?
    //TODO: Pop loop labels from bindings
}