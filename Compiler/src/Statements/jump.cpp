#include "Statements/jump.h"

void ReturnStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "ReturnStatement::print\tSTART\n";

    if (expression)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the return expression is not NULL)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tPrint return expression\n";
        expression->print(out, bindings);
    }

    std::cerr << GlobalIndent::instance().globalIndent << "Print MIPS code\n";
    out << Mips::jump();

    std::cerr << GlobalIndent::instance().globalIndent << "ReturnStatement::print\tEND\n";
};