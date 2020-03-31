#include "../../include/Function/fn_definition.h"

void FnDefinition::print(std::ostream &out, LocalVariableBindings *bindings) const
{
    std::string functionIdentifier = fnDeclarator->getIdentifier()->getName();

    if (GlobalVariableBindings::instance().functionBindingExists(functionIdentifier) == false) //if it hasn't been declared before
    {
        if (returnType == "int")
        {
            GlobalVariableBindings::instance().insertFunctionBinding(functionIdentifier, INTEGER);
        }
        else if (returnType == "void")
        {
            GlobalVariableBindings::instance().insertFunctionBinding(functionIdentifier, VOID);
        }
    }

    LocalVariableBindings *localVariableBindings = new LocalVariableBindings(0, 4); // KIMON CHECK IS THIS RIGHT?

    out << Mips::segment_text();
    out << Mips::tag_global(functionIdentifier);

    out << Mips::new_label(functionIdentifier);

    out << Mips::store_word(31, 0, true); // $31 = $ra
    out << Mips::store_word(30, 4, true); // $30 = $fp

    out << Mips::move(30, 29);

    localVariableBindings->increaseStackFrameSizeBy(8);

    std::vector<ParameterDeclaration *> paramList = fnDeclarator->getParameterList()->getItems();

    for (int i = 0; i < paramList.size(); i++)
    {
        std::string parameterSpecifier = paramList.at(i)->getSpecifier();
        std::string parameterIdentifier = paramList.at(i)->getDeclarator()->getIdentifier()->getName();
        bool isFn = paramList.at(i)->getDeclarator()->isFunction;

        if (isFn)
        {
            if (parameterSpecifier == "void")
            {
                GlobalVariableBindings::instance().insertFunctionBinding(parameterIdentifier, VOID);
            }
            else if (parameterSpecifier == "int")
            {
                GlobalVariableBindings::instance().insertFunctionBinding(parameterIdentifier, INTEGER);
            }
        }
        else
        {
            if (parameterSpecifier == "int")
            {
                localVariableBindings->insertLocalVariableBinding(parameterIdentifier, INTEGER);
            }
        }
    }

    compound->print(out, localVariableBindings);

    out << Mips::load_word(31, 0, false);
    out << Mips::load_word(30, 4, false);

    out << Mips::move(29, 30);

    out << Mips::jump();
}