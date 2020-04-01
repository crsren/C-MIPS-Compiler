#include "../../include/Statements/switch.h"

void SwitchStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << "SwitchStatement::print\tSTART\n";

    // Cast List to labeledStatementList
    std::cerr << "Cast the statementList to a pointer to a LabeledStatementList\n";
    const LabeledStatementList *lsList = dynamic_cast<const LabeledStatementList *>(sList);

    std::cerr << "Getting the END label\n";
    std::string END = Label::instance().uniquify("switch_end");

    std::cerr << "Print the switch statement condition\n";
    condition->print(out, bindings);

    std::cerr << "Print MIPS code\n";
    out << Mips::move(3, 2); // valid case value in $3

    // Branching conditions
    std::cerr << "for (evey labeled statement element in the labeled statement list)\n";
    for (const auto &labeledStatement : lsList->items)
    {
        std::cerr << "\t**************************\n";
        if (!labeledStatement->constExpression)
        { //case x : ...
            std::cerr << "\tif (the current labeled statement is not NULL)\n";
            std::cerr << "\t\tGetting the CASE labels\n";
            std::string CASE = Label::instance().uniquify("case");
            std::cerr << "\t\tSet the label for the current labeled statement\n";
            labeledStatement->setLabel(CASE);

            std::cerr << "\t\tPrint the current labeled statement\n";
            labeledStatement->constExpression->print(out, bindings); // case value in $2
            std::cerr << "\t\tPrint MIPS code\n";
            out << Mips::beq(2, 3, CASE);                            // if this is the valid case, branch to it
        }
        else
        { // default : ...
            std::cerr << "\tif (the current labeled statement is NULL)\n";
            std::cerr << "\t\tPrint the current labeled statement\n";
            labeledStatement->constExpression->print(out, bindings);

            // cases after default will never be reached
            std::cerr << "\t\tPrint MIPS code\n";
            out << Mips::branch(END);
            break;
        }
        std::cerr << "\t**************************\n\n";
    }

    // Statement of each case
    std::cerr << "for (evey labeled statement element in the labeled statement list)\n";
    for (const auto &labeledStatement : lsList->items)
    {
        std::cerr << "\t**************************\n";
        if (!labeledStatement->constExpression)
        {
            std::cerr << "\tif (the current labeled statement is not NULL)\n";
            
            std::cerr << "\t\tPrint MIPS code\n";
            out << Mips::new_label(labeledStatement->getLabel());

            std::cerr << "\t\tPrint the current labeled statement\n";
            labeledStatement->statement->print(out, bindings);
            
            std::cerr << "\t\tPrint MIPS code\n";
            out << Mips::branch(END);
        }
        std::cerr << "\t**************************\n\n";
        
        // dont print case statements that appear after default since they will never be reached
        break;
    }

    std::cerr << "SwitchStatement::print\tEND\n";
}