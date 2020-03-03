#ifndef ASTnode_H
#define ASTnode_H

#include <iostream>
#include <string>

class Indent
{
    int count;

public:
    Indent(int initial) : count(initial){};

    void operator++(int)
    {
        count++;
    };
    void operator--(int)
    {
        count--;
    };

    std::string operator()()
    {
        return std::string(count, ' ');
    };
};

Indent indent(0);

class Node
{
public:
    virtual ~Node(){};
    virtual void print(std::ostream &out) const = 0; //printing python equivalent
};

typedef const Node *nodePtr;

#endif // ASTnode_H
