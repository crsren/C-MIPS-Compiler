#include "Statements/while.h"

void WhileStatement::print(std::ostream &out, VariableBindings &bindings) const
{
    // No need to enter scope as this is done in the compound statement

    std::string WHILE = Label::instance().uniquify("while_c");
    std::string DO = Label::instance().uniquify("while_do");

    //TODO: Add loop labels to bindings

    // CHECK if break is needed
    out << Mips::branch(WHILE);

    out << Mips::new_label(DO);
    statement->print(out, bindings);

    out << Mips::new_label(WHILE);
    condition->print(out, bindings);
    out << Mips::bne(0, 2, DO);

    //CHECK: need break label?
    //TODO: Pop loop labels from bindings
}
