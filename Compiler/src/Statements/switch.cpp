#include "../../include/Statements/switch.h"

void SwitchStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "SwitchStatement::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Getting the END label\n";
    std::string END = Label::instance().uniquify("switch_end");
    std::string DEFAULT = Label::instance().uniquify("default");

    // Adding end label to bindings (for break)
    bindings->push_endLabel(END);

    std::cerr << GlobalIndent::instance().globalIndent << "Print the switch statement condition\n";
    condition->print(out, bindings);

    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::move(3, 2); // valid case value in $3

    // Branching conditions
    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";
    std::cerr << GlobalIndent::instance().globalIndent << "for (evey statement element in the statement list (SIZE: " << sList->getSize() << "))\n";

    std::vector<std::string> labels;
    for (auto &statement : sList->getItems())
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";

        const LabeledStatement *labeledStatement = dynamic_cast<const LabeledStatement *>(statement);
        if (labeledStatement)
        {
            if (labeledStatement->getConstExpression())
            { //case x : ...
                std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement has a constant expression)\n";

                std::cerr << GlobalIndent::instance().globalIndent << "\tCreate a label for every statement\n";

                std::string CASE = Label::instance().uniquify("case");
                //labeledStatement->setLabel(CASE);
                labels.push_back(CASE);

                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled expression\n";
                labeledStatement->getConstExpression()->print(out, bindings); // case value in $2

                out << Mips::beq(2, 3, CASE); // if this is the valid case, branch to it
            }
            else
            { // default : ...
                labels.push_back(DEFAULT);
                out << Mips::branch(DEFAULT);
            }
        }
        else
        { // regular statement -> unlabeled
            labels.push_back("unlabeled-placeholder");
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
        if (labeledStatement)
        {
            if (labeledStatement->getConstExpression())
            {
                std::cerr << GlobalIndent::instance().globalIndent << "if (the current labeled statement is not the default)\n";

                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint MIPS code\n";
                out << Mips::new_label(labels.at(i));

                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the current labeled statement: " << labels.at(i) << "\n";
                if (labeledStatement->getStatement())
                    labeledStatement->getStatement()->print(out, bindings);
            }
            else
            { //default expression
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrint the default labeled statement: " << labels.at(i) << "\n";
                out << Mips::new_label(labels.at(i));
                if (labeledStatement->getStatement())
                    labeledStatement->getStatement()->print(out, bindings);
            }
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
        }
        else
        { // regular statement
            std::cerr << GlobalIndent::instance().globalIndent << "Print regular statement \n";
            if (statements.at(i))
                statements.at(i)->print(out, bindings);
        }
    }

    GlobalIndent::instance().globalIndent = oldGlobalIndent;

    out << Mips::new_label(END);

    bindings->pop_endLabel();

    std::cerr << GlobalIndent::instance().globalIndent << "SwitchStatement::print\tEND\n";
}