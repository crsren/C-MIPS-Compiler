#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "../helpers.h"

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
        std::cerr << "Constant::print\tSTART\n";
        if (bindings != nullptr) // KIMON is this supposed to be local?
        {
            std::cerr << "if (this is a LOCAL constant expression)\n";
            std::cerr << "\tPrinting MIPS code\n";
            out << Mips::load_immediate(8, value);
            out << Mips::store_word(8, bindings->getCurrentExpressionAddressOffset(), false);
            std::cerr << "\tIncrement local stack frame size\n";
            bindings->incrementStackFrameSize();
            //stackFrame->Push(); TODO
        }
        else // global
        {
            std::cerr << "if (this is a GLOBAL constant expression)\n";
            std::cerr << "\tPrinting MIPS code\n";
            std::cerr << "\tIncrement 'global' stack frame size\n";
        }
        std::cerr << "Constant::print\tEND\n";
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
        std::cerr << "Identifier::print\tSTART\n";
        if (bindings->localVariableBindingExists(name))
        {
            std::cerr << "if (the local variable: " << name << " exists)\n";
            std::cerr << "\tPrinting MIPS code\n";
            out << Mips::load_word(2, bindings->getLocalVariableAddressOffset(name), false); // Use frame pointer
        }
        else if (GlobalVariableBindings::instance().globalVariableBindingExists(name))
        {
            std::cerr << "if (the global variable: " << name << " exists)\n";
            std::cerr << "\tPrinting MIPS code\n";
            out << Mips::load_global_word(2, name);
        }
        std::cerr << "Identifier::print\tSTART\n";
    }

    std::string getName() const
    {
        return name;
    }
};

#endif // PRIMITIVES_H
