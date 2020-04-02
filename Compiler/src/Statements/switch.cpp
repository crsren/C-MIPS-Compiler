#include "../../include/Statements/switch.h"

void SwitchStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "SwitchStatement::print\tSTART\n";

    // Cast List to labeledStatementList
    std::cerr << GlobalIndent::instance().globalIndent << "Cast the statementList to a pointer to a LabeledStatementList\n";
    const LabeledStatementList *lsList = dynamic_cast<const LabeledStatementList *>(sList);

    std::cerr << GlobalIndent::instance().globalIndent << "Getting the END label\n";
    std::string END = Label::instance().uniquify("switch_end");

    std::cerr << GlobalIndent::instance().globalIndent << "Print the switch statement condition\n";
    condition->print(out, bindings);

    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::move(3, 2); // valid case value in $3

    // Branching conditions
    std::cerr << GlobalIndent::instance().globalIndent << "for (evey labeled statement element in the labeled statement list)\n";
    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";
    for (const auto &labeledStatement : lsList->items)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
        if (!labeledStatement->constExpression)
        { //case x : ...
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement is not NULL)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tGetting the CASE labels\n";
            std::string CASE = Label::instance().uniquify("case");
            std::cerr << GlobalIndent::instance().globalIndent << "\tSet the label for the current labeled statement\n";
            labeledStatement->setLabel(CASE);

            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled statement\n";
            labeledStatement->constExpression->print(out, bindings); // case value in $2
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::beq(2, 3, CASE);                            // if this is the valid case, branch to it
        }
        else
        { // default : ...
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement is NULL)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled statement\n";
            labeledStatement->constExpression->print(out, bindings);

            // cases after default will never be reached
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::branch(END);
            break;
        }
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
    }
    GlobalIndent::instance().globalIndent = oldGlobalIndent;

    // Statement of each case
    std::cerr << GlobalIndent::instance().globalIndent << "for (evey labeled statement element in the labeled statement list)\n";
    oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";
    for (const auto &labeledStatement : lsList->items)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
        if (!labeledStatement->constExpression)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement is not NULL)\n";
            
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::new_label(labeledStatement->getLabel());

            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled statement\n";
            labeledStatement->statement->print(out, bindings);
            
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::branch(END);
        }
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
        
        // dont print case statements that appear after default since they will never be reached
        break;
    }
    GlobalIndent::instance().globalIndent = oldGlobalIndent;

    std::cerr << GlobalIndent::instance().globalIndent << "SwitchStatement::print\tEND\n";
}