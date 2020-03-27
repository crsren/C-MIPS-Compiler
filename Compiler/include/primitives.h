#if !defined(PRIMITIVES_H)
#define PRIMITIVES_H

#include "helpers.h"

// String_Literal?

class Constant : public Node
{
private:
    const double value;

public:
    Constant(const double &value) : value(value){};

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        out << value;
    };
};

class Identifier : public Node
{
private:
    const std::string name;

public:
    Identifier(const std::string &name) : name(name){};

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        out << name;
    };
};

#endif // PRIMITIVES_H
