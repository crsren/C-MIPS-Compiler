#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "../context.hpp"
#include "ast_node.hpp"
#include "ast_data_type.hpp"

#include <cstdint>
#include <memory>
#include <string>

class Expression : public Node
{
protected:
	Expression* nextExpression;
    
public:
	virtual ~Expression(){}

	virtual VariableBindings printMIPS(VariableBindings bindings, int& label_count) const = 0;
	void setNextExpression(Expression* nextExpression_i)
	{
		nextExpression = nextExpression_i;
	}

	virtual DataType* getType(const VariableBindings &bindings) const = 0;
	Expression* getNextExpression() const
	{
		return nextExpression;
	}
};

//*********************************************OperationalExpression*********************************************

class OperationalExpression : public Expression
{
protected:
	Expression* lhs;
	Expression* rhs;

public:
	OperationalExpression(Expression* lhs_i, Expression* rhs_i):
		lhs(lhs_i),
		rhs(rhs_i)
		{}
	virtual ~OperationalExpression()
	{
		delete nextExpression;
		delete lhs;
		delete rhs;
	}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const = 0;

	virtual DataType* getType(const VariableBindings &bindings) const
	{
		return lhs -> getType(bindings);
	}

	Expression* getLhs() const
	{
		return lhs;
	}

	Expression* getRhs() const
	{
		return rhs;
	}
    
	void evaluateExpression(VariableBindings bindings, int &label_count) const;
};

class AddSubExpression : public OperationalExpression
{
private:
	std::string operationSymbol;

public:
	AddSubExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i),
		operationSymbol(operationSymbol_i)
		{}
		

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);

		// when its a pointer added to a non pointer, multiply non pointer by pointer type
		if
		(
			(Pointer*)(lhs->getType(bindings)) != nullptr &&
		   	(Pointer*)(rhs->getType(bindings)) == nullptr &&
		   	(Identifier*)(lhs) != nullptr
		)
		{
			printf("\tsll\t$v1,$v1,%d\n", lhs->getType(bindings)->getSize()/2);
		}
		else if
		(
			(Pointer*)(lhs->getType(bindings)) == nullptr &&
		    (Pointer*)(rhs->getType(bindings)) != nullptr &&
		    (Identifier*)(rhs) != nullptr
		)
		{
			printf("\tsll\t$v0,$v0,%d\n", rhs->getType(bindings)->getSize()/2);
		}
		if(operationSymbol == "+")
		{
			printf("\taddu\t$v0,$v0,$v1\n");
		}
		else if(operationSymbol == "-")
		{
			printf("\tsubu\t$v0,$v0,$v1\n");
		}
		else
		{
			throw std::runtime_error("Error : '"+operationSymbol+"' not recognized");
		}
		// now I have to store it back into the original stack position
		printf("\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;

	}
};

class MulDivExpression : public OperationalExpression
{
private:
	std::string operationSymbol;

public:
	MulDivExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i),
		operationSymbol(operationSymbol_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);

		// when its a pointer added to a non pointer, multiply non pointer by pointer type
		if
		(
			(Pointer*)(lhs->getType(bindings)) != nullptr &&
		   	(Pointer*)(rhs->getType(bindings)) == nullptr &&
		   	(Identifier*)(lhs) != nullptr
		)
		{
			printf("\tsll\t$v1,$v1,%d\n", lhs->getType(bindings)->getSize()/2);
		}
		else if
		(
			(Pointer*)(lhs->getType(bindings)) == nullptr &&
		    (Pointer*)(rhs->getType(bindings)) != nullptr &&
		    (Identifier*)(rhs) != nullptr
		)
		{
			printf("\tsll\t$v0,$v0,%d\n", rhs->getType(bindings)->getSize()/2);
		}
		if(operationSymbol == "*")
		{
			printf("\tmul\t$v0,$v0,$v1\n");
		}
		else if(operationSymbol == "/")
		{
			printf("\tdiv\t$v0,$v0,$v1\n");
			printf("\tmflo\t$v0\n");
		}
		else if(operationSymbol == "%")
		{
			printf("\tdiv\t$v0,$v0,$v1\n");
			printf("\tmfhi\t$v0\n");
		}
		else
		{
			throw std::runtime_error("Error : '"+operationSymbol+"' not recognized");
		}
		// now I have to store it back into the original stack position
		printf("\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class ShiftExpression : public OperationalExpression
{
private:
	std::string operationSymbol;
public:
	ShiftExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i),
		operationSymbol(operationSymbol_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);

		if(operationSymbol == "<<")
		{
			printf("\tsll\t$v0,$v0,$v1\n");
		}
		else if(operationSymbol == ">>")
		{
			printf("\tsra\t$v0,$v0,$v1\n");
		}
		else
		{
			throw std::runtime_error("Error : '"+operationSymbol+"' not recognized");
		}
		// now I have to store it back into the original stack position
		printf("\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class RelationalExpression : public OperationalExpression
{
private:
	std::string operationSymbol;
public:
	RelationalExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i),
		operationSymbol(operationSymbol_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);

		if(operationSymbol == "<")
		{
			printf("\tslt\t$v0,$v0,$v1\n");
		}
		else if(operationSymbol == ">")
		{
			printf("\tslt\t$v0,$v1,$v0\n");
		}
		if(operationSymbol == "<=")
		{
			printf("\tslt\t$v0,$v1,$v0\n\txori\t$v0,$v0,0x1\n");
		}
		else if(operationSymbol == ">=")
		{
			printf("\tslt\t$v0,$v0,$v1\n\txori\t$v0,$v0,0x1\n");
		}
		else
		{
			throw std::runtime_error("Error : '"+operationSymbol+"' not recognized");
		}
		// now I have to store it back into the original stack position
		printf("\tandi\t$v0,$v0,0x00ff\n\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class EqualityExpression : public OperationalExpression
{
private:
	std::string operationSymbol;
public:
	EqualityExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i),
		operationSymbol(operationSymbol_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);

		printf("\txor\t$v0,$v0,$v1\n");

		if(operationSymbol == "==")
		{
			printf("\tsltiu\t$v0,$v0,1\n");
		}
		else if(operationSymbol == "!=")
		{
			printf("\tsltu\t$v0,$zero,$v0\n");
		}
		else
		{
			throw std::runtime_error("Error : '"+operationSymbol+"' not recognized");
		}
		// now I have to store it back into the original stack position
		printf("\tandi\t$v0,$v0,0x00ff\n\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class AndExpression : public OperationalExpression
{
public:
	AndExpression(Expression* lhs_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);



		printf("\tand\t$v0,$v0,$v1\n\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class ExclusiveOrExpression : public OperationalExpression
{
public:
	ExclusiveOrExpression(Expression* lhs_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);



		printf("\txor\t$v0,$v0,$v1\n\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class InclusiveOrExpression : public OperationalExpression
{
public:
	InclusiveOrExpression(Expression* lhs_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);
		// store the stackPosition of the lhs (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the lhs on the stack
		int lhsRelativeStackFramePosition = -bindings.getStackFrameSize();

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);



		printf("\tor\t$v0,$v0,$v1\n\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class LogicalAndExpression : public OperationalExpression
{
public:
	LogicalAndExpression(Expression* lhs_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		int logicalAndLabelCount = label_count++;
		lhs -> printMIPS(bindings, label_count);
		printf("\tbeq\t$v0,$zero,$%d_logical_and_expression_false\n\tnop\n", logicalAndLabelCount);
		rhs -> printMIPS(bindings, label_count);
		printf("\tbeq\t$v0,$zero,$%d_logical_and_expression_false\n\tnop\n", logicalAndLabelCount);
		printf("\tli\t$v0,1\n");
		printf("\tb\t$%d_logical_and_expression_end\n\tnop\n", logicalAndLabelCount);
		printf("$%d_logical_and_expression_false:\n", logicalAndLabelCount);
		printf("\tmove\t$v0,$zero\n");
		printf("$%d_logical_and_expression_end:\n", logicalAndLabelCount)
		printf("\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class LogicalOrExpression : public OperationalExpression
{
public:
	LogicalOrExpression(Expression* lhs_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		int logicalOrLabelCount = label_count++;
		lhs -> printMIPS(bindings, label_count);
		printf("\tbne\t$v0,$zero,$%d_logical_or_expression_true\n\tnop\n", logicalOrLabelCount);
		rhs -> printMIPS(bindings, label_count);
		printf("\tbne\t$v0,$zero,$%d_logical_or_expression_true\n\tnop\n", logicalOrLabelCount);
		printf("\tmove\t$v0,$zero\n");
		printf("\tb\t$%d_logical_or_expression_end\n\tnop\n", logicalOrLabelCount);
		printf("$%d_logical_or_expression_true:\n", logicalOrLabelCount);
		printf("\tli\t$v0,1\n");
		printf("$%d_logical_or_expression_end:\n", logicalOrLabelCount)
		printf("\tsw\t$v0,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}
};

class AssignmentExpression : public OperationalExpression
{
public:
	AssignmentExpression(Expression* lhs_i, Expression* rhs_i):
		OperationalExpression(lhs_i, rhs_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		// TODO add stack and store results in there, also for addition and multiplication.

		// get the current location of lhs in the stack so that I can store result there
		UnaryExpression* lhsPostfixExpression = (UnaryExpression*) lhs;

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// store the current stackPosition (i.e. the value that must be subtracted from
		// the frame pointer) to get the memory location of the expression on the stack
		int currentRelativeStackFramePosition = -bindings.getStackFrameSize();
		// evaluate rhs and push the result at the above stack position
		// NOTE that since there is no lhs to evaluate there is no reason
		// to increment the stack pointer
		rhs -> printMIPS(bindings, label_count);

		bindings.incrementStackFrameSize();
		printf("\taddiu\t$sp,$sp,-%d\n", 4);
		// print the rhs of the expression
		rhs -> printMIPS(bindings, label_count);
		
		printf("\tlw\t$v0,%d($fp)\n", lhsRelativeStackFramePosition);
		printf("\tlw\t$v1,-%d($fp)\n", bindings.getStackFrameSize());
		bindings.decrementStackFrameSizeBy(bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);
		printf("\taddiu\t$sp,$sp,%d\n", bindings.getStackFrameSize() + lhsRelativeStackFramePosition + 4);

		// get the current available stack position
		int expression_stack_position = bindings.getStackFrameSize();

		// evaluate rhs and get the result back at the stack position I assigned
		// don't have to change the stack position as there is no lhs to evaluate
		rhs_->printMIPS(bindings, label_count);
		bindings.nextExpressionStackPosition();
	
		std::shared_ptr<StringLiteral> rhs_tmp_string;
		std::shared_ptr<OperatorUnaryExpression> rhs_tmp_address;
		rhs_tmp_string = std::dynamic_pointer_cast<StringLiteral>(rhs_);
		rhs_tmp_address = std::dynamic_pointer_cast<OperatorUnaryExpression>(rhs_);
	
		// we are assigning so we don't have to evaluate the lhs as it will be overwritten anyways
		if(rhs_tmp_string != nullptr)
		{
			lhsPostfixExpression->pointerPosition(bindings);
		}
		else if(rhs_tmp_address != nullptr && rhs_tmp_address->getOperator() == "&")
		{
			lhsPostfixExpression->pointerPosition(bindings);
		}
		else
		{
			lhsPostfixExpression->stackPosition(bindings, label_count);
		}
	
		// now the result of the rhs will be in that stack position, so we can load it into $2
		printf("\tlw\t$2,%d($fp)\n", expression_stack_position);
	
		DataType* lhs_type = lhs_->getType(bindings);
		// check if lhs is trying to access an array
		std::shared_ptr<PostfixArrayElement> lhs_tmp;
		lhs_tmp = std::dynamic_pointer_cast<PostfixArrayElement>(lhs_);

		if(lhs_tmp != nullptr)
		{
			std::shared_ptr<Pointer> lhs_pointer_type;
			lhs_pointer_type = std::dynamic_pointer_cast<Pointer>(lhs_type);
			if(lhs_pointer_type != nullptr)
			{
				lhs_pointer_type->pointerStore();
			}
			else
			{
				lhs_type->store();
			}
		}
		else
		{
			lhs_type->store();
		}

		return bindings;
	}
};

//***************************************************************************************************************

//*********************************************UnaryExpression*********************************************

class UnaryExpression : public Expression
{
public:
	virtual void pointerPosition(VariableBindings bindings) const;
	virtual void stackPosition(VariableBindings bindings, int &depth_count) const;
};

class PostfixArrayElement : public UnaryExpression
{
private:
	Expression* postfixExpression;
	Expression* indexExpression;
    
public:
	PostfixArrayElement(Expression* postfixExpression_i, Expression* indexExpression_i):
		postfixExpression(postfixExpression_i),
		indexExpression(indexExpression_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		PostfixArrayElement* arrayElement = (PostfixArrayElement*) postfixExpression;
    
		std::vector<int> arrayDimensionalSizes = bindings.getVariableArrayDimensionSizes( postfixExpression -> getIdentifier() );
	
		int counter = 1;
		printf("\tmove\t$t1,$0\n");
		indexExpression -> printMIPS(bindings, label_count);
		printf("\taddu\t$t1,$t1,$v0\n");    
		while(arrayElement != nullptr)
		{
			arrayElement -> getIndexExpression() -> printMIPS(bindings, label_count);
			int sum = 0;
			for(int i = arrayDimensionalSizes.size() - counter; i < arrayDimensionalSizes.size(); i++)
			{
				sum += arrayDimensionalSizes[i];
			}
			printf("\tmul\t$v0,$v0,%d\n", sum);
			printf("\taddu\t$t1,$t1,$v0\n");
			arrayElement = (PostfixArrayElement*) ( arrayElement -> getPostfixExpression() );
			counter++;
		}
		auto identifierExpression = (Identifier*) ( postfixExpression -> getIdentifier() );
		identifierExpression -> stackPosition(bindings, label_count);
		printf("\tsll\t$t1,$t1,%d\n", postfixExpression -> getType(bindings) -> getSize()/2);
		printf("\taddu\t$t0,$t0,$t1\n");

		DataType* type_ptr = postfixExpression -> getType(bindings);
		Pointer* pointer_type_ptr = (Pointer*) (type_ptr);
		if(pointer_type_ptr != nullptr)
		{
			pointer_type_ptr -> pointerLoad();
		}
		else
		{
			type_ptr -> load();
		}
		printf("\tsw\t$2,%d($fp)\n", bindings.getStackFrameSize());
		return bindings;
	}

	virtual DataType* getType(const VariableBindings &bindings) const
	{
		return postfixExpression -> getType(bindings);
	}

	virtual std::string getIdentifier() const
	{
		return postfixExpression -> getIdentifier();
	}

	Expression* getIndexExpression() const
	{
		return indexExpression;
	}

	Expression* getPostfixExpression() const
	{
		return postfixExpression;
	}
};

class PostfixFunctionCall : public UnaryExpression
{
private:
	Expression* postfixExpression;
	Expression* argumentExpressionList;
    
public:
	PostfixFunctionCall(Expression* argumentExpressionList_i)
		argumentExpressionList(argumentExpressionList_i)
		{}

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const
	{
		std::vector<Expression*> vectorOfArguments;
		Expression* current_argument = argument_expression_list_;
		int argument_counter = 0;

		while(current_argument != nullptr)
		{
			vectorOfArguments.push_back(current_argument);
			current_argument = current_argument->nextExpression();
		}

		for(auto itr = vectorOfArguments.rbegin(); itr != vectorOfArguments.rend(); ++itr)
		{
			(*itr)->printAsm(bindings, label_count);

			if(argument_counter < 4)
				printf("\tmove\t$%d,$2\n", 4+argument_counter);
			else
				(*itr)->getType(bindings)->store(4*argument_counter);

			argument_counter++;
		}

		printf("\tjal\t%s\n\tnop\n\tsw\t$2,%d($fp)\n",
		       postfix_expression_->id().c_str(), bindings.currentExpressionStackPosition());
		return bindings;
	}

	virtual void countArguments(int &argument_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
    
	void setPostfixExpression(Expression* postfixExpression_i);
};

class PostfixPostIncDecExpression : public UnaryExpression
{
private:
	std::string operationSymbol;
	Expression* postfixExpression;

public:
	PostfixPostIncDecExpression(const std::string &operationSymbol_i, Expression* postfixExpression_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
    
};

class UnaryPreIncDecExpression : public UnaryExpression
{
private:
	std::string operationSymbol;
	Expression* unary_expression_;
    
public:
	UnaryPreIncDecExpression(const std::string &operationSymbol_i, Expression* unary_expression);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

class OperatorUnaryExpression : public UnaryExpression
{
private:
	std::string operationSymbol;
	Expression* cast_expression_;

public:
	OperatorUnaryExpression(const std::string &operationSymbol_i, Expression* cast_expression);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual void stackPosition(VariableBindings bindings, int &depth_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
	std::string getOperator() const;
};

class Identifier : public UnaryExpression
{
private:
	std::string id_;
public:
	Identifier(const std::string &id);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual void pointerPosition(VariableBindings bindings) const;
	virtual void stackPosition(VariableBindings bindings, int &depth_count) const;
	virtual std::string getIdentifier() const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

class StringLiteral : public UnaryExpression
{
private:
	std::string string_content_;
public:
	StringLiteral(const std::string &string_content);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

class Constant : public UnaryExpression
{
private:
	int32_t constant_;
public:
	Constant(const int32_t &constant);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

//*********************************************************************************************************

class Initializer : public Expression
{
private:
	Expression* next_initializer_;
public:
	Initializer(Expression* next_initializer);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;

	void printInitializerAsm(VariableBindings &bindings, int &label_count, int position, const std::vector<int> &iteration_vector, const DataType* &type) const;
	Expression* getNext() const;
};

class ConditionalExpression : public Expression
{
private:
	Expression* logical_or_;
	Expression* expression_;
	Expression* conditional_expression_;

public:
	ConditionalExpression(Expression* logical_or, Expression* expression,
	                      Expression* conditional_expression);
    
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

class CastExpression : public Expression
{
private:
	DataType* type_;
	Expression* expression_;

public:
	CastExpression(DataType* type, Expression* expression);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

#endif