#include "Statements/selection.h"

void IfElseStatement::print(std::ostream &out, VariableBindings bindings) const
{

    // enter scope? (or is this done in compound)

    std::string ELSE = Label::instance().uniquefy("else");
    std::string END = Label::instance().uniquefy("end");

    condition->print(out, bindings);

    out << Mips::beq(0, 2, ELSE); //if false, jump to else

    statement1->print(out, bindings); // if statement

    out << Mips::branch(END);

    out << Mips::label(ELSE);

    if (has_else)
        statement2->print(out, bindings);

    out << Mips::label(END);
};
