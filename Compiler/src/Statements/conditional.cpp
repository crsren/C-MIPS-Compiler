#include "Statements/conditional.h"

//TODO: Switch

void IfElseStatement::print(std::ostream &out, VariableBindings &bindings) const
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

// void SwitchStatement::print(std::ostream &out, VariableBindings &bindings) const
// {

// }

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