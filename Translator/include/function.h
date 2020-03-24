#ifndef FUNCTION_H
#define FUNCTION_H

#include "node.h"

#include <list>

class FnParameter : public Node
{
private:
    nodePtr declarator;

public:
    FnParameter(nodePtr d) : declarator(d){};

    virtual void print(std::ostream &out) const override
    {
        declarator->print(out);
    };

    ~FnParameter()
    {
        delete declarator;
    };
};

class FnDeclarator : public Node
{
private:
    nodePtr declarator;
    nodePtr list;

public:
    FnDeclarator(nodePtr d) : declarator(d), list(){};
    FnDeclarator(nodePtr d, nodePtr l) : declarator(d), list(l){};

    virtual void print(std::ostream &out) const override
    {
        declarator->print(out);

        out << "(";
        if (list != nullptr)
        {
            list->print(out);
        }
        out << ")";
    };

    ~FnDeclarator()
    {
        delete declarator;
    };
};

class FnDefinition : public Node
{
private:
    nodePtr declarator;
    nodePtr compoundStatement;

public:
    FnDefinition(nodePtr d, nodePtr c) : declarator(d), compoundStatement(c){};

    virtual void print(std::ostream &out) const override
    {
        out << Indent::instance() << "def ";
        declarator->print(out);
        out << ":\n";
        out << Global::instance();
        compoundStatement->print(out);
        out << '\n';
    };

    ~FnDefinition()
    {
        delete declarator;
        delete compoundStatement;
    };
};

#endif // FUNCTION_H
