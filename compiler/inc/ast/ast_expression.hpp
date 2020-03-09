#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "bindings.hpp"
#include "node.hpp"
#include "type.hpp"

#include <cstdint>
#include <memory>
#include <string>

class Expression : public Node
{
protected:
	Expression* next_expression_;
    
public:
	virtual VariableBindings printAsm(VariableBindings bindings, int& label_count) const = 0;
    
	virtual int constantFold() const;
	virtual void print() const;
	virtual void printXml() const;
	virtual void countArguments(int &argument_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual std::string id() const;
	virtual DataType* getType(const VariableBindings &bindings) const = 0;
       
	void linkExpression(Expression* next_expression);
	Expression* nextExpression() const;
};

//*********************************************OperationalExpression*********************************************

class OperationExpression : public Expression
{
protected:
	Expression* lhs_;
	Expression* rhs_;
public:
	OperationExpression(Expression *lhs, Expression *rhs);
	OperationExpression(Expression* lhs, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const = 0;
    
	virtual int constantFold() const;
	virtual void expressionDepth(int &depth_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;

	Expression* getLhs() const;
	Expression* getRhs() const;
    
	void evaluateExpression(VariableBindings bindings, int &label_count) const;
};

class AdditiveExpression : public OperationExpression
{
private:
	std::string operator_;

public:
	AdditiveExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class MultiplicativeExpression : public OperationExpression
{
private:
	std::string operator_;

public:
	MultiplicativeExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class ShiftExpression : public OperationExpression
{
private:
	std::string operator_;
public:
	ShiftExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class RelationalExpression : public OperationExpression
{
private:
	std::string operator_;
public:
	RelationalExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class EqualityExpression : public OperationExpression
{
private:
	std::string operator_;
public:
	EqualityExpression(Expression *lhs, const std::string &_operator, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class AndExpression : public OperationExpression
{
public:
	AndExpression(Expression *lhs, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class ExclusiveOrExpression : public OperationExpression
{
public:
	ExclusiveOrExpression(Expression *lhs, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class InclusiveOrExpression : public OperationExpression
{
public:
	InclusiveOrExpression(Expression *lhs, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const; 
};

class LogicalAndExpression : public OperationExpression
{
public:
	LogicalAndExpression(Expression *lhs, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
};

class LogicalOrExpression : public OperationExpression
{
public:
	LogicalOrExpression(Expression *lhs, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;    
};

class AssignmentExpression : public OperationExpression
{
public:
	AssignmentExpression(Expression *lhs, Expression *rhs);
	AssignmentExpression(Expression* lhs, Expression *rhs);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
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
	PostfixArrayElement(Expression *postfix_expression, Expression *index_expression);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
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
	PostfixFunctionCall(Expression *argument_expression_list = nullptr);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual void countArguments(int &argument_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
    
	void setPostfixExpression(Expression *postfix_expression);
};

class PostfixPostIncDecExpression : public UnaryExpression
{
private:
	std::string operator_;
	Expression* postfix_expression_;

public:
	PostfixPostIncDecExpression(const std::string &_operator, Expression *postfix_expression);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
    
};

class UnaryPreIncDecExpression : public UnaryExpression
{
private:
	std::string operator_;
	Expression* unary_expression_;
    
public:
	UnaryPreIncDecExpression(const std::string &_operator, Expression *unary_expression);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

class OperatorUnaryExpression : public UnaryExpression
{
private:
	std::string operator_;
	Expression* cast_expression_;

public:
	OperatorUnaryExpression(const std::string &_operator, Expression *cast_expression);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
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

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
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

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

class Constant : public UnaryExpression
{
private:
	int32_t constant_;
public:
	Constant(const int32_t &constant);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual int constantFold() const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

//*********************************************************************************************************

class Initializer : public Expression
{
private:
	Expression* next_initializer_;
public:
	Initializer(Expression *next_initializer);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
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
	ConditionalExpression(Expression *logical_or, Expression *expression,
	                      Expression *conditional_expression);
    
	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

class CastExpression : public Expression
{
private:
	DataType* type_;
	Expression* expression_;

public:
	CastExpression(DataType *type, Expression *expression);

	virtual VariableBindings printAsm(VariableBindings bindings, int &label_count) const;
	virtual void expressionDepth(int &depth_count) const;
	virtual DataType* getType(const VariableBindings &bindings) const;
};

#endif