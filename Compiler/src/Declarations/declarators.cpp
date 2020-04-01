#include "../../include/Declaration/declarators.h"

void InitDeclarator::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::string identifier = declarator->getIdentifier()->getName();
    // this.specifierType is the type (got this from declaration class before this print function is being called )

    if ((specifierType == "") && (initializer != nullptr) && !(declarator->isFunction)) // the variable has already been declared and we assign a value to it
    {
        if (bindings == nullptr) // global
        {
            initializer->print(out, bindings);
            out << Mips::load_address(1, identifier);
            out << Mips::store_word_reg(2, 0, 1);
        }

        else // local
        {
            initializer->print(out, bindings);
            out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
        }
    }

    else if (specifierType == "int") // the variable is being declared
    {
        if ((initializer != nullptr) && !(declarator->isFunction)) // we assign a value to the variable being declared
        {
            if (bindings == nullptr) // global
            {
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);

                out << Mips::segment_text();
                initializer->print(out, bindings);
                out << Mips::load_address(1, identifier);
                out << Mips::store_word_reg(2, 0, 1);
            }
            else // local
            {
                bindings->insertLocalVariableBinding(identifier, _INTEGER);
                initializer->print(out, bindings);
                out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
            }
        }
        else if ((initializer == nullptr) && !(declarator->isFunction)) // the variable is just declared without being initialized
        {
            if (bindings == nullptr) // global
            {
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);

                out << Mips::segment_text();
            }
            else // local
            {
                bindings->insertLocalVariableBinding(identifier, _INTEGER);
                out << Mips::store_word(0, bindings->getLocalVariableAddressOffset(identifier), false);
            }
        }
        else if ((initializer == nullptr) && (declarator->isFunction))
        {
            GlobalVariableBindings::instance().insertFunctionBinding(identifier, _INTEGER);
        }
    }

    else if ((specifierType == "void") && (initializer == nullptr) && (declarator->isFunction)) // the function is being declared
    {
        GlobalVariableBindings::instance().insertFunctionBinding(identifier, _VOID);
    }
};