#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "node.h"
#include <iostream>
#include <list>

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
        std::cerr << "inifStatement!" << std::endl;

        out << Indent::instance() << "if (";
        std::cerr << "afterif, 20:10:34" << std::endl;
        condition->print(out);
        out << Indent::instance() << "):\n";
        Indent::instance()++;
        statement1->print(out);
        Indent::instance()--;

        if (has_else)
        {
            out << Indent::instance() << "\nelse:\n";
            Indent::instance()++;
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
        std::cout << "Iteration, 20:08:43" << std::endl;
        out << Indent::instance() << "while (";
        condition->print(out);
        out << Indent::instance() << "):\n";
        Indent::instance()++;
        statement->print(out);
        Indent::instance()--;
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
        std::cout << "Jump, 19:55:29" << std::endl;
        out << Indent::instance() << "return ";
        if (expression != NULL)
            expression->print(out);
        std::cout << "Jump2, 19:55:48" << std::endl;
        out << '\n';
    };

    ~Jump()
    {
        delete expression;
    };
};

class Assignment : public Node
{
private:
    nodePtr unary, expression;

public:
    Assignment(nodePtr u, nodePtr exp) : unary(u), expression(exp){};

    virtual void print(std::ostream &out) const override
    {
        std::cout << "Assignment, 20:04:56" << std::endl;
        out << Indent::instance();
        unary->print(out);
        out << " = ";
        expression->print(out);
        out << '\n';
    };

    ~Assignment()
    {
        delete unary;
        delete expression;
    };
};

class Compound : public Node
{
private:
    nodePtr dList;
    nodePtr sList;

public:
    Compound(nodePtr d, nodePtr s) : dList(d), sList(s){};

    virtual void print(std::ostream &out) const override
    {
        std::cout << "Compound, 20:05:06" << std::endl;
        Indent::instance()++;

        if (dList != NULL)
            dList->print(out);
        std::cout << "inbetween, 20:06:39" << std::endl;

        if (sList != NULL)
            sList->print(out);

        Indent::instance()--;
    };
};

#endif // STATEMENTS_H
