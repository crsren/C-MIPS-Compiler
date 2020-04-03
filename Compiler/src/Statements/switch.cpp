#include "../../include/Statements/switch.h"

void SwitchStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "SwitchStatement::print\tSTART\n";

    // Cast List to labeledStatementList
    std::cerr << GlobalIndent::instance().globalIndent << "Cast the statementList to a pointer to a LabeledStatementList\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Getting the END label\n";
    std::string END = Label::instance().uniquify("switch_end");

    // Adding end label to bindings (for break)
    bindings->push_endLabel(END);

    std::cerr << GlobalIndent::instance().globalIndent << "Print the switch statement condition\n";
    condition->print(out, bindings);

    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::move(3, 2); // valid case value in $3

    // Branching conditions
    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";
    std::cerr << GlobalIndent::instance().globalIndent << "for (evey labeled statement element in the labeled statement list)\n";

    std::vector<std::string> labels;
    for (auto &statement : sList->getItems())
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";

        const LabeledStatement *labeledStatement = dynamic_cast<const LabeledStatement *>(statement);

        if (!labeledStatement->getConstExpression())
        { //case x : ...
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement has a constant expression)\n";

            std::cerr << GlobalIndent::instance().globalIndent << "\tCreate a label for every statement\n";

            std::string CASE = Label::instance().uniquify("case");
            //labeledStatement->setLabel(CASE);
            labels.push_back(CASE);

            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled statement\n";
            labeledStatement->getConstExpression()->print(out, bindings); // case value in $2
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::beq(2, 3, CASE); // if this is the valid case, branch to it
        }
        else
        { // default : ...
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement is NULL)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled statement\n";
            if (labeledStatement->getStatement())
                labeledStatement->getStatement()->print(out, bindings);

            // cases after default will never be reached
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::branch(END);
            break;
        }
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
    }
    GlobalIndent::instance().globalIndent = oldGlobalIndent;

    // Statement of each switch case
    std::cerr << GlobalIndent::instance().globalIndent << "for (evey labeled statement element in the labeled statement list)\n";
    oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";

    auto statements = sList->getItems();
    for (auto i = 0; i < labels.size(); i++)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";

        const LabeledStatement *labeledStatement = dynamic_cast<const LabeledStatement *>(statements.at(i));

        if (!labeledStatement->getConstExpression())
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement is not the default)\n";

            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
            out << Mips::new_label(labels.at(i));

            std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled statement\n";
            if (labeledStatement->getStatement())
                labeledStatement->getStatement()->print(out, bindings);
        }
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
    }

    GlobalIndent::instance().globalIndent = oldGlobalIndent;

    Mips::new_label(END);

    bindings->pop_endLabel();

    std::cerr << GlobalIndent::instance().globalIndent << "SwitchStatement::print\tEND\n";
}