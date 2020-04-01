#include "../../include/Function/fn_definition.h"

void FnDefinition::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << "FnDefinition::print\tSTART\n";

    std::cerr << "Get the function identifier\n";
    std::string functionIdentifier = fnDeclarator->getIdentifier()->getName();

    if (!GlobalVariableBindings::instance().functionBindingExists(functionIdentifier)) //if it hasn't been declared before
    {
        std::cerr << "if (the global function: " << functionIdentifier << " has not been declared)\n";
        if (returnType == "int")
        {
            std::cerr << "\tif (the global function's: " << functionIdentifier << " return type is int)\n";
            std::cerr << "\t\tInsert the global function: " << functionIdentifier << " into the functionBindings\n";
            GlobalVariableBindings::instance().insertFunctionBinding(functionIdentifier, _INTEGER);
        }
        else if (returnType == "void")
        {
            std::cerr << "\tif (the global function's: " << functionIdentifier << " return type is void)\n";
            std::cerr << "\t\tInsert the global function: " << functionIdentifier << " into the functionBindings\n";
            GlobalVariableBindings::instance().insertFunctionBinding(functionIdentifier, _VOID);
        }
    }

    std::cerr << "Declare a pointer to a new LocalVariableBindings object\n";
    LocalVariableBindings *localVariableBindings = new LocalVariableBindings(0, 4); // KIMON CHECK IS THIS RIGHT?

    std::cerr << "Printing MIPS code\n";
    out << Mips::segment_text();
    out << Mips::tag_global(functionIdentifier);

    out << Mips::new_label(functionIdentifier);

    out << Mips::store_word(31, 0, true); // $31 = $ra
    out << Mips::store_word(30, 4, true); // $30 = $fp

    out << Mips::move(30, 29);

    std::cerr << "Increase the local bindings' stack frame size by 8\n";
    localVariableBindings->increaseStackFrameSizeBy(8);

    std::cerr << "Cast the fnDeclarator to a pointer to a FnDeclarator\n";
    const FnDeclarator *cast_fnDeclarator = dynamic_cast<const FnDeclarator *>(fnDeclarator);

    std::vector<const ParameterDeclaration*> paramList;
    if (cast_fnDeclarator->getParameterList())
    {
        std::cerr << "if (the parameter list is not a null pointer)\n";
        std::cerr << "\tGet the parameter list and assign it to a vector\n";
        paramList = cast_fnDeclarator->getParameterList()->getItems();
    }

    std::cerr << "for (evey argument in the argument list)\n";
    for (int i = 0; i < paramList.size(); i++)
    {
        std::cerr << "\t**************************\n";
        std::cerr << "\tLoop Iteration:" << std::to_string(i) << "\n";

        std::cerr << "\tGet the current parameter's type specifier\n";
        std::string parameterSpecifier = paramList.at(i)->getSpecifier();

        std::cerr << "\tGet the current parameter's identifier\n";
        std::string parameterIdentifier = paramList.at(i)->getDeclarator()->getIdentifier()->getName();

        std::cerr << "\tCheck whether the current parameter is a function\n";
        bool isFn = paramList.at(i)->getDeclarator()->isFunction;

        if (isFn)
        {
            std::cerr << "\tif (the current parameter is a function)\n";
            if (parameterSpecifier == "void")
            {
                std::cerr << "\t\tif (the return type of the function is void)\n";
                std::cerr << "\t\t\tInsert Global Function Binding\n";
                GlobalVariableBindings::instance().insertFunctionBinding(parameterIdentifier, _VOID);
            }
            else if (parameterSpecifier == "int")
            {
                std::cerr << "\t\tif (the return type of the function is int)\n";
                std::cerr << "\t\t\tInsert Global Function Binding\n";
                GlobalVariableBindings::instance().insertFunctionBinding(parameterIdentifier, _INTEGER);
            }
        }
        else
        {
            std::cerr << "\tif (the current parameter is a variable)\n";
            if (parameterSpecifier == "int")
            {
                std::cerr << "\t\tif (the type of the variable is int)\n";
                std::cerr << "\t\t\tInsert Local Variable Binding\n";
                localVariableBindings->insertLocalVariableBinding(parameterIdentifier, _INTEGER);
            }
        }
        std::cerr << "\t**************************\n\n";
    }

    std::cerr << "Print the compound statement\n";
    compound->print(out, localVariableBindings);

    std::cerr << "Printing MIPS code\n";
    out << Mips::load_word(31, 0, false);
    out << Mips::load_word(30, 4, false);

    out << Mips::move(29, 30);

    out << Mips::jump();

    std::cerr << "FnDefinition::print\tEND\n";
}