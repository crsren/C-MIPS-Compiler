#if !defined(VARIABLE_H)
#define VARIABLE_H

#include "AST.h"

class VarDeclarator : public Node
{
private:
    nodePtr declarator, expression;

public:
    VarDeclarator(nodePtr d, nodePtr exp) : declarator(d), expression(exp){};
    VarDeclarator(nodePtr d) : declarator(d), expression(nullptr){};

    virtual void print(std::ostream &out) const override
    {
        if (Indent::instance().getCount())
        {
            Global::instance().add(declarator->getContent());
        }

        out << Indent::instance();
        declarator->print(out);
        out << "=";
        if (expression)
            out << "0";
        else
            expression->print(out);
        out << '\n';
    };

    ~VarDeclarator()
    {
        delete declarator;
        delete expression;
    };
};

#endif // VARIABLE_H
