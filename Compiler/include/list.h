#ifndef LIST_H
#define LIST_H

#include "helpers.h"

#include <list>

// https://stackoverflow.com/questions/31513730/building-a-linked-list-in-yacc-with-left-recursive-grammar

class List : public Node
{
private:
    std::list<nodePtr> items;

public:
    List(nodePtr first)
    {
        items.push_back(first);
    };

    void print(std::ostream &out, VariableBindings bindings) const override
    {
        for (const auto &i : items)
            i->print(out, bindings);
    }

    virtual void add(nodePtr ptr)
    {
        items.push_back(ptr);
    };
};

#endif // LIST_H
