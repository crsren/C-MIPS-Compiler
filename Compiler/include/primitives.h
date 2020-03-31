#ifndef PRIMITIVES_H
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

    void print(std::ostream &out, LocalVariableBindings & bindings) const override
    {
        if(bindings)
        {
            out << Mips::load_immediate(8, value);
            out << Mips::store_word(8, bindings.getCurrentExpressionAddressOffset(), false);
            //stackFrame->Push(); TODO
        }
        else
        {

        }
    };
};

class Identifier
{
private:
    const std::string name;

public:
    Identifier(const std::string &name) : name(name){};

    std::string getName() {
        return name;
    }
};

#endif // PRIMITIVES_H
