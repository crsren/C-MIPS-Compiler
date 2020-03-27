#include "Statements/jump.h"

void ReturnStatement::print(std::ostream &out, !!!) const
{
    if (expression)
        expression->print(out, !!!);

    out << Mips::jump();
};