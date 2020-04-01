#include "Statements/jump.h"

void ReturnStatement::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    if (expression)
        expression->print(out, bindings);

    out << Mips::jump();
};