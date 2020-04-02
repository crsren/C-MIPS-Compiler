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
    Constant(double &value) : value(value){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "Constant::print\tSTART\n";
        if (bindings != nullptr) // KIMON is this supposed to be local?
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (this is a LOCAL constant expression)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
            out << Mips::load_immediate(2, value);
            out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
            std::cerr << GlobalIndent::instance().globalIndent << "\tIncrement local stack frame size\n";
            //bindings->incrementCurrentExpressionAddressOffset();
            //stackFrame->Push(); TODO
        }
        else // global
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (this is a GLOBAL constant expression)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tIncrement 'global' stack frame size\n";
        }
        std::cerr << GlobalIndent::instance().globalIndent << "Constant::print\tEND\n";
    };
};

class Identifier : public Node
{
private:
    const std::string name;

public:
    Identifier(std::string &name) : name(name){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "Identifier::print\tSTART\n";
        if (bindings->localVariableBindingExists(name))
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the local variable: " << name << " exists)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
            out << Mips::load_word(2, bindings->getLocalVariableAddressOffset(name), false); // Use frame pointer
        }
        else if (GlobalVariableBindings::instance().globalVariableBindingExists(name))
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the global variable: " << name << " exists)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
            out << Mips::load_global_word(2, name);
        }
        std::cerr << GlobalIndent::instance().globalIndent << "Identifier::print\tEND\n";
    }

    const std::string getName() const
    {
        return name;
    }
};

#endif // PRIMITIVES_H
