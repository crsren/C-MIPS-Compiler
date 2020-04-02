#include "../../include/Declaration/declarators.h"

void InitDeclarator::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "InitDeclarator::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Getting the idenifier of the declarator\n";
    std::string identifier = declarator->getIdentifier()->getName();
    // this.specifierType is the type (got this from declaration class before this print function is being called )

    if ((specifierType == "") && (initializer != nullptr) && !(declarator->isFunction)) // the variable has already been declared and we assign a value to it
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the VARIABLE has already been declared and is modified)\n";
        if (bindings == nullptr) // global
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is global)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrint the initializer\n";
            initializer->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrinting MIPS code\n";
            out << Mips::load_address(1, identifier);
            out << Mips::store_word_reg(2, 0, 1);
        }

        else // local
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is local)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrint the initializer\n";
            initializer->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrinting MIPS code\n";
            out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
        }
    }

    else if (specifierType == "int") // the variable is being declared
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the identifier is being declared as an int)\n";
    
        if ((initializer != nullptr) && !(declarator->isFunction)) // we assign a value to the variable being declared
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is modified)\n";
            if (bindings == nullptr) // global
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is global)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Global Variable Binding\n";
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);

                out << Mips::segment_text();

                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrint the initializer\n";
                initializer->print(out, bindings);
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
                out << Mips::load_address(1, identifier);
                out << Mips::store_word_reg(2, 0, 1);
            }
            else // local
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is local)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Local Variable Binding\n";
                bindings->insertLocalVariableBinding(identifier, _INTEGER);
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrint the initializer\n";
                initializer->print(out, bindings);
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
                out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
            }
        }
        else if ((initializer == nullptr) && !(declarator->isFunction)) // the variable is just declared without being initialized
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is JUST being declared)\n";
            if (bindings == nullptr) // global
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is global)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Global Variable Binding\n";
                GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
                out << Mips::segment_data();
                out << Mips::word_data(identifier, 0);

                out << Mips::segment_text();
            }
            else // local
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is local)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Local Variable Binding\n";
                bindings->insertLocalVariableBinding(identifier, _INTEGER);
                std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
                out << Mips::store_word(0, bindings->getLocalVariableAddressOffset(identifier), false);
            }
        }
        else if ((initializer == nullptr) && (declarator->isFunction))
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the FUNCTION is JUST being declared)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert Global Function Binding\n";
            GlobalVariableBindings::instance().insertFunctionBinding(identifier, _INTEGER);
        }
    }

    else if ((specifierType == "void") && (initializer == nullptr) && (declarator->isFunction)) // the function is being declared
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the FUNCTION is JUST being declared as a void)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tInsert Global Function Binding\n";
        GlobalVariableBindings::instance().insertFunctionBinding(identifier, _VOID);
    }

    std::cerr << GlobalIndent::instance().globalIndent << "InitDeclarator::print\tEND\n";
};