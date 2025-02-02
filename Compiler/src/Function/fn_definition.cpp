#include "../../include/Function/fn_definition.h"

void FnDefinition::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::cerr << GlobalIndent::instance().globalIndent << "FnDefinition::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Get the function identifier\n";
    std::string functionIdentifier = fnDeclarator->getIdentifier()->getName();

    const FnDeclarator *cast_fnDeclarator = dynamic_cast<const FnDeclarator *>(fnDeclarator);
    std::vector<const ParameterDeclaration *> paramList;
    int paramListSize = 0;
    if (cast_fnDeclarator->getParameterList())
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the parameter list is not a null pointer)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tGet the parameter list and assign it to a vector\n";
        paramList = cast_fnDeclarator->getParameterList()->getItems();
        paramListSize = cast_fnDeclarator->getParameterList()->getSize();
    }

    if (!GlobalVariableBindings::instance().functionBindingExists(functionIdentifier)) //if it hasn't been declared before
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the global function: " << functionIdentifier << " has not been declared)\n";

        if (returnType == "int")
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the global function's: " << functionIdentifier << " return type is int)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert the global function: " << functionIdentifier << " into the functionBindings\n";
            GlobalVariableBindings::instance().insertFunctionBinding(functionIdentifier, _INTEGER, 0, false);
        }
        else if (returnType == "void")
        {
            std::cerr << GlobalIndent::instance().globalIndent << "\tif (the global function's: " << functionIdentifier << " return type is void)\n";
            std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert the global function: " << functionIdentifier << " into the functionBindings\n";
            GlobalVariableBindings::instance().insertFunctionBinding(functionIdentifier, _VOID, 0, false);
        }
    }

    std::cerr << GlobalIndent::instance().globalIndent << "Declare a pointer to a new LocalVariableBindings object\n";
    LocalVariableBindings *localVariableBindings = new LocalVariableBindings(); // KIMON CHECK IS THIS RIGHT?

    std::cerr << GlobalIndent::instance().globalIndent << "Printing MIPS code\n";

    out << Mips::function_prologue(functionIdentifier);

    std::cerr << GlobalIndent::instance().globalIndent << "Increase the local bindings' stack frame size by 8\n";
    localVariableBindings->increaseStackFrameSizeBy(8);

    std::cerr << GlobalIndent::instance().globalIndent << "Cast the fnDeclarator to a pointer to a FnDeclarator\n";

    std::cerr << GlobalIndent::instance().globalIndent << "for (evey parameter in the parameter list)\n";
    std::cerr << GlobalIndent::instance().globalIndent << "paramListSize:" << paramListSize << "\n";
    std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
    GlobalIndent::instance().globalIndent += "\t";
    for (int i = paramListSize - 1; i >= 0; i--)
    {
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
        std::cerr << GlobalIndent::instance().globalIndent << "Loop Iteration:" << std::to_string(paramListSize - i) << "\n";

        std::cerr << GlobalIndent::instance().globalIndent << "Get the current parameter's type specifier\n";
        std::string parameterSpecifier = paramList[i]->getSpecifier();

        std::cerr << GlobalIndent::instance().globalIndent << "Get the current parameter's identifier\n";
        std::string parameterIdentifier = paramList[i]->getDeclarator()->getIdentifier()->getName();

        std::cerr << GlobalIndent::instance().globalIndent << "Check whether the current parameter is a function\n";
        bool isFn = paramList[i]->getDeclarator()->isFunction;

        if (isFn)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current parameter is a function)\n";
            if (parameterSpecifier == "void")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\tif (the return type of the function is void)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert Global Function Binding\n";
                GlobalVariableBindings::instance().insertFunctionBinding(parameterIdentifier, _VOID, 0, false);
            }
            else if (parameterSpecifier == "int")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\tif (the return type of the function is int)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert Global Function Binding\n";
                GlobalVariableBindings::instance().insertFunctionBinding(parameterIdentifier, _INTEGER, 0, false);
            }
        }
        else
        {
            std::cerr << GlobalIndent::instance().globalIndent << "if (the current parameter is a variable)\n";
            if (parameterSpecifier == "int")
            {
                std::cerr << GlobalIndent::instance().globalIndent << "\tif (the type of the variable is int)\n";
                std::cerr << GlobalIndent::instance().globalIndent << "\t\tInsert Local Variable Binding\n";
                if (i < 4)
                {
                    localVariableBindings->insertLocalVariableBinding(parameterIdentifier, _INTEGER, -(i + 1), false); // $a0, $a1, $a2, $a3
                }
                else
                {
                    localVariableBindings->insertLocalVariableBinding(parameterIdentifier, _INTEGER, -4*(i - 3) - 1, false);   // $a4, ..., $a_n
                }
            }
        }
        std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
    }
    GlobalIndent::instance().globalIndent = oldGlobalIndent;

    std::cerr << GlobalIndent::instance().globalIndent << "Print the compound statement\n";
    compound->print(out, localVariableBindings);

    if (returnType == "void")
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the return type of the function: " << fnDeclarator->getIdentifier()->getName() << " is void)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tPrinting MIPS code\n";
        out << Mips::function_epilogue();
    }

    std::cerr << GlobalIndent::instance().globalIndent << "FnDefinition::print\tEND\n";
}