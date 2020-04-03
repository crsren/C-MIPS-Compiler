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
            //std::cerr << GlobalIndent::instance().globalIndent << "\tIncrement local stack frame size\n";
            //bindings->incrementCurrentExpressionAddressOffset();
            //stackFrame->Push(); TODO
        }
        else // global
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (this is a GLOBAL constant expression)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
            out << Mips::load_immediate(2, value);
            out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
        }
        std::cerr << GlobalIndent::instance().globalIndent << "Constant::print\tEND\n";
    };

    int getValue() const
    {
        return value;
    }
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
            out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
        }
        else if (GlobalVariableBindings::instance().globalVariableBindingExists(name))
        {
            if (bindings)
            {
                std::cerr << GlobalIndent::instance().globalIndent << "if (the global variable: " << name << " exists)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
                out << Mips::load_global_word(2, name);
                out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
            }
            else
            {
                std::cerr << GlobalIndent::instance().globalIndent << "if (the global variable: " << name << " exists)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
                out << Mips::load_global_word(2, name);
                out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
            }
        }
        std::cerr << GlobalIndent::instance().globalIndent << "Identifier::print\tEND\n";
    }

    const std::string getName() const
    {
        return name;
    }
};

class Array : public Node
{
    nodePtr postfix_exp;
    nodePtr index_exp;
    std::string variableName;

public:
    Array(nodePtr postfix_exp, nodePtr index_exp) : postfix_exp(postfix_exp), index_exp(index_exp)
    {
        const Identifier *identifier = dynamic_cast<const Identifier *>(postfix_exp);

        // ASSUME INDEX_EXPR IS SIMPLE CONSTANT
        const Constant *constantVal;
        if (index_exp)
            constantVal = dynamic_cast<const Constant *>(index_exp);

        // construct var name
        variableName = identifier->getName() + std::to_string(constantVal->getValue());
    };

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {

        // dependent on if local / global
        // treat as normal int identifier

        std::cerr << GlobalIndent::instance().globalIndent << "Identifier::print\tSTART\n";
        if (bindings->localVariableBindingExists(variableName))
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the local variable: " << variableName << " exists)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
            out << Mips::load_word(2, bindings->getLocalVariableAddressOffset(variableName), false); // Use frame pointer
            out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
        }
        else if (GlobalVariableBindings::instance().globalVariableBindingExists(variableName))
        {
            if (bindings) //local
            {
                std::cerr << GlobalIndent::instance().globalIndent << "if (the global variable: " << variableName << " exists)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
                out << Mips::load_global_word(2, variableName);
                out << Mips::store_word(2, bindings->getCurrentExpressionAddressOffset(), false);
            }
            else // global
            {
                std::cerr << GlobalIndent::instance().globalIndent << "if (the global variable: " << variableName << " exists)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
                out << Mips::load_global_word(2, variableName);
                out << Mips::store_word(2, GlobalVariableBindings::instance().getCurrentGlobalExpressionAddressOffset(), false);
            }
        }
        std::cerr << GlobalIndent::instance().globalIndent << "Identifier::print\tEND\n";
    }

    const std::string getName() const
    {
        return variableName;
    }
};

#endif // PRIMITIVES_H
