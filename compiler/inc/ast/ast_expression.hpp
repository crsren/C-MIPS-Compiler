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
		// print the lhs of the expression
		lhs -> printMIPS(bindings, label_count);

		// store the relative memory location of the lhs on the stack
		rhs -> printMIPS(bindings, label_count);
		
		std::
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

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class ShiftExpression : public OperationalExpression
{
private:
	std::string operationSymbol;
public:
	ShiftExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class RelationalExpression : public OperationalExpression
{
private:
	std::string operationSymbol;
public:
	RelationalExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class EqualityExpression : public OperationalExpression
{
private:
	std::string operationSymbol;
public:
	EqualityExpression(Expression* lhs_i, const std::string &operationSymbol_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class AndExpression : public OperationalExpression
{
public:
	AndExpression(Expression* lhs_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class ExclusiveOrExpression : public OperationalExpression
{
public:
	ExclusiveOrExpression(Expression* lhs_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class InclusiveOrExpression : public OperationalExpression
{
public:
	InclusiveOrExpression(Expression* lhs_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class LogicalAndExpression : public OperationalExpression
{
public:
	LogicalAndExpression(Expression* lhs_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class LogicalOrExpression : public OperationalExpression
{
public:
	LogicalOrExpression(Expression* lhs_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class AssignmentExpression : public OperationalExpression
{
public:
	AssignmentExpression(Expression* lhs_i, Expression* rhs_i);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

//***************************************************************************************************************

//*********************************************UnaryExpression*********************************************

class UnaryExpression : public Expression
{
public:
	virtual void expressionDepth(int &depth_count) const;
	virtual void pointerPosition(VariableBindings bindings) const;
	virtual void stackPosition(VariableBindings bindings, int &depth_count) const;
};

class PostfixArrayElement : public UnaryExpression
{
private:
	Expression* postfix_expression_;
	Expression* index_expression_;
    
public:
	PostfixArrayElement(Expression* postfix_expression, Expression* index_expression);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual void stackPosition(VariableBindings bindings, int &depth_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
	virtual std::string id() const;

	Expression* getIndex() const;
	Expression* getPostfix() const;    
};

class PostfixFunctionCall : public UnaryExpression
{
private:
	Expression* postfix_expression_;
	Expression* argument_expression_list_;
    
public:
	PostfixFunctionCall(Expression* argument_expression_list = nullptr);

	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
    
	void setPostfixExpression(Expression* postfix_expression);
};

class PostfixPostIncDecExpression : public UnaryExpression
{
private:
	std::string operationSymbol;
	Expression* postfix_expression_;

public:
	PostfixPostIncDecExpression(const std::string &operationSymbol_i, Expression* postfix_expression);

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
	virtual std::string id() const;
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
	virtual void expressionDepth(int &depth_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

#endif