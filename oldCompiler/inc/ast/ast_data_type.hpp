#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP

#include "../context.hpp"
#include "ast_node.hpp"

#include <memory>
#include <string>

class DataType : public Node
{
public:
	virtual void print() const = 0;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const = 0;
    
	virtual DataType* type() = 0;
	virtual DataType* type(DataType* type_ptr) = 0;
};

class Array : public DataType
{
private:
	int size_;
	DataType* type_;

public:
	Array(const int &size, DataType* type_ = nullptr);

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
    
	virtual DataType* type();
	virtual DataType* type(DataType* type_ptr);
};

class Pointer : public DataType
{
private:
	DataType* type_;
public:
	Pointer();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
    
	virtual DataType* type();
	virtual DataType* type(DataType* type_ptr);
};

class TypeContainer : public DataType
{
protected:
	DataType* type_;
	int size_;
	bool extern_;
	bool static_;
	bool const_;
	bool signed_;

public:
	TypeContainer();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
    
	virtual DataType* type();
	virtual DataType* type(DataType* type_ptr);
};

class Primitive : public DataType
{
public:
	virtual void print() const = 0;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const = 0;

	virtual DataType* type();
	virtual DataType* type(DataType* type_ptr);
};

class Int : public Primitive
{
public:
	Int();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class Double : public Primitive
{
public:
	Double();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class Unsigned : public Primitive
{
public:
	Unsigned();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class Void : public Primitive
{
public:
	Void();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class Char : public Primitive
{
public:
	Char();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

class Float : public Primitive
{
public:
	Float();

	virtual void print() const;
	virtual VariableBindings printMIPS(VariableBindings bindings, int &label_count) const;
};

#endif