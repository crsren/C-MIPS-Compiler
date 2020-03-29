#if !defined(PRIMITIVES_H)
#define PRIMITIVES_H

#include "helpers.h"

// String_Literal?
// TO DO: these classes might have a type parent class

class Constant : public Node
{
private:
    const double value;

public:
    Constant(const double &value) : value(value){};

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        // This must be in local scope TODO
        // if (stackFrame == nullptr)
        //     return;

        out << Mips::load_immediate(8, value);
        out << Mips::store_word(8, bindings.getCurrentExpressionAddressOffset(), false);
        //stackFrame->Push(); TODO
    };
};

//TODO: IMPLEMENT PRINT
class Identifier : public Node
{
private:
    const std::string name;

public:
    Identifier(const std::string &name) : name(name){};
};

#endif // PRIMITIVES_H
