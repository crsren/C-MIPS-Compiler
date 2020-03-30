#include "../../include/Declaration/declarators.h"

void InitDeclarator::print(std::ostream &out, LocalVariableBindings &bindings) const override
{
    std::string identifier = declarator -> getIdentifier();
    // this.specifierType is the type (got this from declaration class before this print function is being called )

    if (specifierType == "" && initializer != nullptr) // the variable has already been defined and we assign a value to it
    {
        if (bindings == NULL) // global
        {
            initializer -> print(out, bindings);
            out << Mips::load_address(1, identifier);
            out << Mips::store_word_reg(2, 0, 1);
        }

        else // local
        {
            initializer -> print(out, bindings);
            out << Mips::store_word(2, bindings.getLocalVariableAddressOffset(identifier), false);
        }
    }

    else if (specifierType == "int") // the variable is being declared
    {
        if (initializer != nullptr) // we assign a value to the variable being declared
        {
            if(bindings == NULL) // global
            {
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, INTEGER);
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);
                
                out << Mips::segment_text();
                initializer -> print(out, bindings);
                out << Mips::load_address(1, identifier);
                out << Mips::store_word_reg(2, 0, 1);
            }
            else // local
            {
                bindings.insertLocalVariableBinding(identifier, INTEGER);
                initializer -> print(out, bindings);
                out << Mips::store_word(2, bindings.getLocalVariableAddressOffset(identifier), false);
            }
        }
        else // the variable is just declared without being initialized
        {
             if(bindings == NULL) // global
            {
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, INTEGER);
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);
                
                out << Mips::segment_text(); // ****************************************NOT SURE**************************************
            }
            else // local
            {
                bindings.insertLocalVariableBinding(identifier, INTEGER);
                out << Mips::store_word(0, bindings.getLocalVariableAddressOffset(identifier), false);
            }
        }
    }

    else if (specifierType == "void") // the variable is being declared
    {
        if (initializer != nullptr) // we assign a value to the variable being declared
        {
            if(bindings == NULL) // global
            {
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, INTEGER);
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);
                
                out << Mips::segment_text();
                initializer -> print(out, bindings);
                out << Mips::load_address(1, identifier);
                out << Mips::store_word_reg(2, 0, 1);
            }
            else // local
            {
                bindings.insertLocalVariableBinding(identifier, INTEGER);
                initializer -> print(out, bindings);
                out << Mips::store_word(2, bindings.getLocalVariableAddressOffset(identifier), false);
            }
        }
        else // the variable is just declared without being initialized
        {
             if(bindings == NULL) // global
            {
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, INTEGER);
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);
                
                out << Mips::segment_text(); // ****************************************NOT SURE**************************************
            }
            else // local
            {
                bindings.insertLocalVariableBinding(identifier, INTEGER);
                out << Mips::store_word(0, bindings.getLocalVariableAddressOffset(identifier), false);
            }
        }
    }
};