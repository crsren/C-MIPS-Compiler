#include "Statements/jump.h"

void ReturnStatement::print(std::ostream &out, VariableBindings &bindings) const
{
    if (expression)
        expression->print(out, bindings);

    out << Mips::jump();
};