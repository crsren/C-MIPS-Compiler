#include "Statements/switch.h"

void SwitchStatement::print(std::ostream &out, VariableBindings &bindings) const
{
    std::string END = Label::instance().uniquify("switch_end");

    condition->print(out, bindings);
    out << Mips::move(2, 3); // valid case value in $3

    // Branching conditions
    for (const auto &labeledStatement : lsList->items)
    {
        if (!labeledStatement->constExpression)
        { //case x : ...
            std::string CASE = Label::instance().uniquify("case");
            labeledStatement->setLabel(CASE);

            labeledStatement->constExpression->print(out, bindings); // case value in $2
            out << Mips::beq(2, 3, CASE);                            // if this is the valid case, branch to it
        }
        else
        { // default : ...

            labeledStatement->constExpression->print(out, bindings);

            // cases after default will never be reached
            out << Mips::branch(END);
            break;
        }
    }

    // Statement of each case
    for (const auto &labeledStatement : lsList->items)
    {
        if (!labeledStatement->constExpression)
        {
            out << Mips::new_label(labeledStatement->getLabel());
            labeledStatement->statement->print(out, bindings);
            out << Mips::branch(END);
        }
        // dont print case statements that appear after default since they will never be reached
        break;
    }
}