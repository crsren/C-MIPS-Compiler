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

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        if (bindings) // KIMON is this supposed to be local?
        {
            out << Mips::load_immediate(8, value);
            out << Mips::store_word(8, bindings->getCurrentExpressionAddressOffset(), false);
            //stackFrame->Push(); TODO
        }
        else // global
        {
        }
    };
};

class Identifier : public Node
{
private:
    const std::string name;

public:
    Identifier(const std::string &name) : name(name){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        if (bindings->localVariableBindingExists(name))
        {
            out << Mips::load_word(2, bindings->getLocalVariableAddressOffset(name), false); // Use frame pointer
        }
        else if (GlobalVariableBindings::instance().globalVariableBindingExists(name))
        {
            out << Mips::load_global_word(2, name);
        }
    }

    std::string getName() const
    {
        return name;
    }
};

#endif // PRIMITIVES_H
