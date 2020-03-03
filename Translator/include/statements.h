#if !defined(STATEMENTS_H)
#define STATEMENTS_H

#include "ASTNode.h"
#include <iostream>

class Selection : public Node
{
private:
    nodePtr condition;
    nodePtr statement1;
    nodePtr statement2;
    bool has_else;

public:
    Selection(nodePtr assignmentExp, nodePtr s1) : condition(assignmentExp), statement1(s1), has_else(false){};
    Selection(nodePtr assignmentExp, nodePtr s1, nodePtr s2) : condition(assignmentExp), statement1(s1), statement2(s2), has_else(true){};

    virtual void print(std::ostream &out) const override
    {
        out << indent() << "if (";
        condition->print(out);
        out << indent() << "):\n";
        indent++;
        statement1->print(out);
        indent--;

        if (has_else)
        {
            out << indent() << "\nelse:\n";
            indent++;
            statement2->print(out);
        }
    };

    ~Selection()
    {
        delete condition;
        delete statement1;
        delete statement2;
    }
};

class Iteration : public Node
{
private:
    nodePtr condition;
    nodePtr statement;

public:
    Iteration(nodePtr ae, nodePtr s) : condition(ae), statement(s){};

    virtual void print(std::ostream &out) const override
    {
        out << indent() << "while (";
        condition->print(out);
        out << indent() << "):\n";
        indent++;
        statement->print(out);
        indent--;
    };

    ~Iteration()
    {
        delete condition;
        delete statement;
    }
};

class Jump : public Node
{
private:
    nodePtr expression;

public:
    Jump(nodePtr expr) : expression(expr){};

    virtual void print(std::ostream &out) const override
    {
        out << indent() << "return ";
        if (expression != NULL)
            expression->print(out);
        out << '\n';
    };

    ~Jump()
    {
        delete expression;
    };
};

#endif // STATEMENTS_H
