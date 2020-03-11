#if !defined(FUNCTION_H)
#define FUNCTION_H

#include "AST.h"

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
    std::list<nodePtr> paramList;

public:
    FnDeclarator(nodePtr d) : declarator(d), paramList(){};
    FnDeclarator(nodePtr d, std::list<nodePtr> p) : declarator(d), paramList(p){};

    virtual void print(std::ostream &out) const override
    {
        declarator->print(out);

        out << "(";
        if (paramList.empty())
        { // not empty
            unsigned char separator = 0;
            for (const auto &param : paramList)
            {
                out << separator;
                separator = ',';
                param->print(out);
            };
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
        out << '\n';

        Indent::instance()++;
        out << Global::instance();
        Indent::instance()--;

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
