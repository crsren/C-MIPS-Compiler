#include "Statements/if_else.h"

void IfElseStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    // No need to enter scope as this is done in the compound statement

    std::string ELSE = Label::instance().uniquify("else");
    std::string END = Label::instance().uniquify("fi");

    condition->print(out, bindings);

    out << Mips::beq(0, 2, ELSE); //if false, jump to else

    statement1->print(out, bindings); // if statement

    out << Mips::branch(END);

    out << Mips::new_label(ELSE);

    if (has_else)
        statement2->print(out, bindings);

    out << Mips::new_label(END);
};