#ifndef AST_FUNCTION_HPP
#define AST_FUNCTION_HPP

#include "../context.hpp"
#include "ast_declaration.hpp"
#include "ast_node.hpp"
#include "ast_statement.hpp"
#include "ast_data_type.hpp"

#include <memory>
#include <string>

class Function : public Node
{
protected:
	DataType* returnType;
	std::string functionIdentifier;
	Statement* linkedListOfFunctionStatements;
	Declaration* linkedListOfLocalVariableDeclarations;
    
public:
	Function(const std::string& functionIdentifier_i, Statement* linkedListOfFunctionStatements_i, Declaration* linkedListOfLocalVariableDeclarations_i = nullptr):
        functionIdentifier(functionIdentifier_i),
        linkedListOfFunctionStatements(linkedListOfFunctionStatements_i),
        linkedListOfLocalVariableDeclarations(linkedListOfLocalVariableDeclarations_i)
    {}

	virtual VariableBindings printMIPS(VariableBindings localBindings, int& label_count) const
    {
        int numberOfLocalVariables = 0;
		if(linkedListOfFunctionStatements != NULL)
		{
			linkedListOfFunctionStatements -> countLocalVariables(numberOfLocalVariables);
		}

		int maxNumberOfFunctionArguments = 0;
		if(linkedListOfFunctionStatements != NULL)
		{
			linkedListOfFunctionStatements -> countFunctionArguments(maxNumberOfFunctionArguments);
		}

		if(maxNumberOfFunctionArguments < 4)
		{
			maxNumberOfFunctionArguments = 4;
		}

		// we add 2 since we need to store the return address as well as the frame pointer
		int necessaryStackFrameSize = numberOfLocalVariables + maxNumberOfFunctionArguments + 2;

		// we need to ensure that the stack frame size is divisible by 8
		int necessaryStackFramePads = necessaryStackFrameSize % 8;
		necessaryStackFrameSize += necessaryStackFramePads;

		// we multiply by 4 to get the actual byte addressing right
		necessaryStackFrameSize *= 4;

		printf("\t.text\n\t.align\t2\n\t.globl\t%s\n%s:\n",
	       functionIdentifier, functionIdentifier);
		printf("\t#start of function prologue\n");
		printf("\taddiu\t$sp,$sp,-%d\n\tsw\t$ra,%d($sp)\n\tsw\t$fp,%d($sp)\n\taddiu\t$fp,$sp,-%d\n",
			necessaryStackFrameSize,
			necessaryStackFrameSize - numberOfLocalVariables - 4,
			necessaryStackFrameSize - numberOfLocalVariables - 8,
			necessaryStackFrameSize - 4);
		printf("\t#end of function prologue\n\n");

		// initialize our local function bindings
		VariableBindings localFunctionBindings(necessaryStackFrameSize);

		//****************************************************************************
		printf("\t#start of setting up function data\n");
		std::vector<Declaration*> vectorOfLocalVariableDeclarations;
		Declaration* currentLocalVariableDeclaration = linkedListOfLocalVariableDeclarations;

		while(currentLocalVariableDeclaration != nullptr)
		{
			vectorOfLocalVariableDeclarations.push_back(currentLocalVariableDeclaration);
			currentLocalVariableDeclaration = currentLocalVariableDeclaration -> getNext();
		}

		for(int i = vectorOfLocalVariableDeclarations.size() - 1; i >= 0; i--)
		{
			int j = (vectorOfLocalVariableDeclarations.size() - 1) - i;
			localFunctionBindings.insertBinding
			(
				(*vectorOfLocalVariableDeclarations[i]) -> getIdentifier(),
				(*vectorOfLocalVariableDeclarations[i]) -> getDataType(),
				necessaryStackFrameSize - j*4
			);

			DataType* parameterDataType = (*vectorOfLocalVariableDeclarations[i]) -> getType();

			if(j < 4)
			{    
				parameterDataType -> store(4 + j, necessaryStackFrameSize - j*4);
			}
			else
			{
				if(std::dynamic_pointer_cast<TypeContainer>(parameterDataType) != nullptr)
				{
					if(std::dynamic_pointer_cast<Char>(parameterDataType->type()) != nullptr)
					{    
						printf("\tlw\t$2,%d($sp)\n", necessaryStackFrameSize - j*4);
						printf("\tsb\t$2,%d($sp)\n", necessaryStackFrameSize - j*4);
					}
					else if(std::dynamic_pointer_cast<Short>(parameterDataType->type()) != nullptr)
					{
						printf("\tlw\t$2,%d($sp)\n", necessaryStackFrameSize - j*4);
						printf("\tsh\t$2,%d($sp)\n", necessaryStackFrameSize - j*4);
					}
				}
			}
		}
		printf("\t#end of setting up function data\n\n");
		//****************************************************************************
		
		printf("\t#start of function body\n");
		linkedListOfFunctionStatements -> printMIPS(localFunctionBindings, label_count);
		printf("\t#end of function body\n\n");

		printf("\t#start of function epilogue\n");
		printf("\tmove\t$v0,$zero\n\tlw\t$ra,%d($sp)\n", necessaryStackFrameSize - numberOfLocalVariables - 4,);
		printf("\tlw\t$fp,%d($sp)\n", necessaryStackFrameSize - numberOfLocalVariables - 8,);
		printf("\taddiu\t$sp,$sp,%d\n\tjr\t$ra\n\tnop\n", necessaryStackFrameSize);
		printf("\t#end of function epilogue\n");

		return localBindings;
    }

	void countParameters(int& parameter_count) const;
};

#endif
