#ifndef DECLARATION_H
#define DECLARATION_H

#include "node.h"

// // for for var, function, (later array?)
// class Declaration : public Node
// {
//     //nodePtr dataType; for now this is a single string
//     const std::string declarationSpecifier;
//     nodePtr initDeclaratorList; // TO DO: this should be VarDeclarator*

// public:
//     Declaration(const std::string dS, nodePtr iDL) : declarationSpecifier(dS), initDeclaratorList(iDL){};

//     ~Declaration()
//     {
//         delete initDeclaratorList;
//     }

//     void print(std::ostream &out, VariableBindings &bindings) const override
//     {
//         initDeclaratorList->print(out, bindings)

//             // if ( LOCAL VARIABLE DECLARATION )
//             int declarationSpecifierCode;
//         if (declarationSpecifier == "int")
//         {
//             bindings.insertLocalVariableBinding(initDeclarator->getIdentifier(), INTEGER);
//         }
//         else if (declarationSpecifier == "double")
//         {
//             bindings.insertLocalVariableBinding(initDeclaratorList.getIdentifier(), DOUBLE);
//         }
//         else if (declarationSpecifier == "float")
//         {
//             bindings.insertLocalVariableBinding(initDeclaratorList.getIdentifier(), FLOAT);
//         }
//         else if (declarationSpecifier == "char")
//         {
//             bindings.insertLocalVariableBinding(initDeclaratorList.getIdentifier(), CHAR);
//         }
//         else if (declarationSpecifier == "unsigned")
//         {
//             bindings.insertLocalVariableBinding(initDeclaratorList.getIdentifier(), UNSIGNED);
//         }

//         out << Mips::store_word(0, bindings.getLocalVariableAddressOffset(initDeclarator.getIdentifier()), false);

//         // else if ( GLOBAL VARIABLE DECLARATION )
//         int declarationSpecifierCode;
//         if (declarationSpecifier == "int")
//         {
//             bindings.insertGlobalVariableBinding(initDeclaratorList.getIdentifier(), INTEGER);
//         }
//         // else if (declarationSpecifier == "double")
//         // {
//         //     bindings.insertGlobalVariableBinding(initDeclaratorList.getIdentifier(), DOUBLE);
//         // }
//         // else if (declarationSpecifier == "float")
//         // {
//         //     bindings.insertGlobalVariableBinding(initDeclaratorList.getIdentifier(), FLOAT);
//         // }
//         // else if (declarationSpecifier == "char")
//         // {
//         //     bindings.insertGlobalVariableBinding(initDeclaratorList.getIdentifier(), CHAR);
//         // }
//         // else if (declarationSpecifier == "unsigned")
//         // {
//         //     bindings.insertGlobalVariableBinding(initDeclaratorList.getIdentifier(), UNSIGNED);
//         // }

//         out << Mips::store_word(0, bindings.getLocalVariableAddressOffset(initDeclarator.getIdentifier()), false);
//     }
// };

#endif // DECLARATION_H