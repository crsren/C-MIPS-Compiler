#include "../../include/Declaration/declarators.h"

// void InitDeclarator::print(std::ostream &out, LocalVariableBindings *bindings) const
// {
//     std::cerr << GlobalIndent::instance().globalIndent << "InitDeclarator::print\tSTART\n";

//     std::cerr << GlobalIndent::instance().globalIndent << "Getting the idenifier of the declarator\n";
//     std::string identifier = declarator->getIdentifier()->getName();
//     // this.specifierType is the type (got this from declaration class before this print function is being called )

//     if (!declarator->isFunction)
//     {
//         if ((specifierType == "") && (initializer != nullptr)) // the variable has already been declared and we assign a value to it
//         {
//             std::cerr << GlobalIndent::instance().globalIndent << "if (the VARIABLE has already been declared and is modified)\n";
//             if (bindings == nullptr) // global
//             {
//                 std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is global)\n";
//                 std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrint the initializer\n";
//                 initializer->print(out, bindings);
//                 std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrinting MIPS code\n";
//                 out << Mips::store_global_word(2, identifier);
//             }
//             else // local
//             {
//                 std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is local)\n";
//                 std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrint the initializer\n";
//                 initializer->print(out, bindings);
//                 std::cerr << GlobalIndent::instance().globalIndent << "\t\tPrinting MIPS code\n";
//                 out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
//             }
//         }
//         else if (specifierType == "int") // int var declaration
//         {
//             std::cerr << GlobalIndent::instance().globalIndent << "if (the identifier is being declared as an int)\n";

//             if (initializer != nullptr) // we assign a value to the variable being declared
//             {
//                 std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is modified)\n";
//                 if (bindings == nullptr) // global
//                 {
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is global)\n";
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Global Variable Binding\n";
//                     GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
//                     out << Mips::segment_data();
//                     out << Mips::word_data(identifier, 0);

//                     out << Mips::segment_text();

//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrint the initializer\n";
//                     initializer->print(out, bindings);
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
//                     out << Mips::store_global_word(2, identifier);
//                 }
//                 else // local
//                 {
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is local)\n";
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Local Variable Binding\n";
//                     bindings->insertLocalVariableBinding(identifier, _INTEGER);
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrint the initializer\n";
//                     initializer->print(out, bindings);
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
//                     out << Mips::store_word(2, bindings->getLocalVariableAddressOffset(identifier), false);
//                 }
//             }
//             else if (initializer == nullptr) // we set the variable equal to zero
//             {
//                 std::cerr << GlobalIndent::instance().globalIndent << "\tif (the VARIABLE is JUST being declared)\n";
//                 if (bindings == nullptr) // global
//                 {
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is global)\n";
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Global Variable Binding\n";
//                     GlobalVariableBindings::instance().insertGlobalVariableBinding(identifier, _INTEGER);
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
//                     out << Mips::segment_data();
//                     out << Mips::word_data(identifier, 0);

//                     out << Mips::segment_text();
//                 }
//                 else // local
//                 {
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\tif (the VARIABLE is local)\n";
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tInsert Local Variable Binding\n";
//                     bindings->insertLocalVariableBinding(identifier, _INTEGER);
//                     std::cerr << GlobalIndent::instance().globalIndent << "\t\t\tPrinting MIPS code\n";
//                     out << Mips::store_word(0, bindings->getLocalVariableAddressOffset(identifier), false);
//                 }
//             }
//         }
//     }
//     else
//     { // is function -> can cast
//         const FnDeclarator *fnDeclarator = dynamic_cast<const FnDeclarator *>(declarator);
//         int numParam = fnDeclarator->getParameterList()->getSize();
//         if ((initializer == nullptr && specifierType == "int"))
//         {
//             std::cerr << GlobalIndent::instance().globalIndent << "\tif (the FUNCTION is JUST being declared)\n";
//             std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert Global Function Binding\n";
//             GlobalVariableBindings::instance().insertFunctionBinding(identifier, _INTEGER, numParam);
//         }
//         else if ((initializer == nullptr) && (specifierType == "void"))
//         {
//             std::cerr << GlobalIndent::instance().globalIndent << "if (the FUNCTION is JUST being declared as a void)\n";
//             std::cerr << GlobalIndent::instance().globalIndent << "\tInsert Global Function Binding\n";
//             GlobalVariableBindings::instance().insertFunctionBinding(identifier, _VOID, numParam);
//         }
//     }
//     std::cerr << GlobalIndent::instance().globalIndent << "InitDeclarator::print\tEND\n";
// };
