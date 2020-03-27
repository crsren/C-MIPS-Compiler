#include "Function/fn_definition.h"

void fnDefinition::print(std::ostream &out, !!!) const
{
    out << Mips::segment_text();
    //get return type
    // declare if it was not already

    std::string name;
    // get function name via declarator
    out << Mips::label(name);
    out << Mips::tag_global(name);

    // New stack frame, new scope
    // Store $fp and $ra //keep in int var for restoring later

    //Compile compound statement

    // restore fp and ra from var

    out << Mips::jump();

    out << Mips::segment_data();

    // Leave scope
}