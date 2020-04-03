#ifndef BOOLEAN_OPERATION_H
#define BOOLEAN_OPERATION_H

#include "binary_operation.h"
#include "../helpers.h"

// <, >, <=, >=, ==, !=
class BooleanOperation : public BinaryOperation
{
public:
    BooleanOperation(nodePtr l, const std::string &s, nodePtr r) : BinaryOperation(l, s, r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

class LogicalAnd : public BinaryOperation
{
public:
    LogicalAnd(nodePtr l, nodePtr r) : BinaryOperation(l, "", r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

class LogicalOr : public BinaryOperation
{
public:
    LogicalOr(nodePtr l, nodePtr r) : BinaryOperation(l, "", r){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;
};

#endif // BOOL_OPERATION_H
