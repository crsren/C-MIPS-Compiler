#include "Statements/jump.h"

void ReturnStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << "ReturnStatement::print\tSTART\n";

    if (expression != nullptr)
    {
        std::cerr << "if (the return expression is not NULL)\n";
        std::cerr << "\tPrint return expression\n";
        expression->print(out, bindings);
    }

    std::cerr << "Print MIPS code\n";
    out << Mips::jump();

    std::cerr << "ReturnStatement::print\tEND\n";
};