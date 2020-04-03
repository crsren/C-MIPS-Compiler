#include "Declaration/init_declarator.h"

void InitDeclarator::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "InitDeclarator::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Getting the idenifier of the declarator\n";
    std::string identifier = declarator->getIdentifier()->getName();
    // this.specifierType is the type (got this from declaration class before this print function is being called )

    if (!declarator->isFunction)
    {
        if ((specifierType == "") && (initializer != nullptr)) // the variable has already been declared and we assign a value to it
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the VARIABLE has already been declared and is modified)\n";
            if (bindings == nullptr) // global
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is global)\n";
                std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
                GlobalIndent::instance().globalIndent += "\t\t";
                std::cerr << GlobalIndent::instance().globalIndent << "Print the initializer\n";
                out << Mips::move(9, 30);
                out << Mips::move(30, 29);
                initializer->print(out, bindings);
                out << Mips::move(30, 9);
                std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
                out << Mips::store_global_word(2, identifier);
                GlobalIndent::instance().globalIndent = oldGlobalIndent;
            }
            else // local
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is local)\n";
                std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
                GlobalIndent::instance().globalIndent += "\t\t";
                std::cerr << GlobalIndent::instance().globalIndent << "Print the initializer\n";
                initializer->print(out, bindings);
                std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
                out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
                GlobalIndent::instance().globalIndent = oldGlobalIndent;
            }
        }
        else if (specifierType == "int") // int var declaration
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the identifier is being declared as an int)\n";

            if (initializer != nullptr) // we assign a value to the variable being declared
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is modified)\n";
                if (bindings == nullptr) // global
                {
                    std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is global)\n";
                    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
                    GlobalIndent::instance().globalIndent += "\t\t\t";
                    std::cerr << GlobalIndent::instance().globalIndent << "Insert Global Variable Binding\n";

                    //GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
                    GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER, false);

                    // We know the initializer will be a simple constant
                    const Constant *constant = dynamic_cast<const Constant *>(initializer);
                    int constValue = constant->getValue();

                    GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER, false);

                    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
                    out << Mips::segment_data();

                    out << Mips::word_data(identifier, constValue);

                    out << Mips::segment_text();

                    std::cerr << GlobalIndent::instance().globalIndent << "Print the initializer\n";
                    out << Mips::move(9, 30);
                    out << Mips::move(30, 29);
                    initializer->print(out, bindings);
                    out << Mips::move(30, 9);
                    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
                    out << Mips::store_global_word(2, identifier);
                    GlobalIndent::instance().globalIndent = oldGlobalIndent;
                }
                else // local
                {
                    std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is local)\n";
                    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
                    GlobalIndent::instance().globalIndent += "\t\t\t";
                    std::cerr << GlobalIndent::instance().globalIndent << "Insert Local Variable Binding\n";
                    bindings->insertLocalVariableBinding(identifier, _INTEGER, false);
                    std::cerr << GlobalIndent::instance().globalIndent << "Print the initializer\n";
                    initializer->print(out, bindings);
                    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
                    out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
                    GlobalIndent::instance().globalIndent = oldGlobalIndent;
                }
            }
            else if (initializer == nullptr) // we set the variable equal to zero
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is JUST being declared)\n";
                if (bindings == nullptr) // global
                {
                    std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is global)\n";
                    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
                    GlobalIndent::instance().globalIndent += "\t\t\t";
                    std::cerr << GlobalIndent::instance().globalIndent << "Insert Global Variable Binding\n";

                    //GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
                    GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER, false);

                    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
                    out << Mips::segment_data();

                    out << Mips::word_data(identifier, 0);

                    out << Mips::segment_text();
                    GlobalIndent::instance().globalIndent = oldGlobalIndent;
                }
                else // local
                {
                    std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is local)\n";
                    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
                    GlobalIndent::instance().globalIndent += "\t\t\t";
                    std::cerr << GlobalIndent::instance().globalIndent << "Insert Local Variable Binding\n";
                    bindings->insertLocalVariableBinding(identifier, _INTEGER, false);
                    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";
                    out << Mips::store_word(0, bindings->getLocalVariableAddressOffset(identifier), false);
                    GlobalIndent::instance().globalIndent = oldGlobalIndent;
                }
            }
        }
    }
    else
    { // is function -> can cast
        const FnDeclarator *fnDeclarator = dynamic_cast<const FnDeclarator *>(declarator);
        int numParam = fnDeclarator->getParameterList()->getSize();
        if ((initializer == nullptr && specifierType == "int"))
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the FUNCTION is JUST being declared)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert Global Function Binding\n";
            GlobalVariableBindings::instance().insertFunctionBinding(identifier, _INTEGER, numParam, false);
        }
        else if ((initializer == nullptr) && (specifierType == "void"))
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the FUNCTION is JUST being declared as a void)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert Global Function Binding\n";
            GlobalVariableBindings::instance().insertFunctionBinding(identifier, _VOID, numParam, false);
        }
    }
    std::cerr << GlobalIndent::instance().globalIndent << "InitDeclarator::print\tEND\n";
};

void InitDeclaratorList::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "for (evey initDeclarator in the list)\n";
    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";
    for (const auto &initDeclarator : items)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
        std::cerr << GlobalIndent::instance().globalIndent << "Print the current initDeclarator\n";
        initDeclarator->print(out, bindings);
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
    }
    GlobalIndent::instance().globalIndent = oldGlobalIndent;
}