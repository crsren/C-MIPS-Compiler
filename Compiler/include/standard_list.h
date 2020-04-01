#ifndef STANDARD_LIST_H
#define STANDARD_LIST_H

#include "helpers.h"

#include <list>

// https://stackoverflow.com/questions/31513730/building-a-linked-list-in-yacc-with-left-recursive-grammar

class List : public Node
{
public:
    std::list<nodePtr> items;
    List(nodePtr first)
    {
        items.push_back(first);
    };

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        for (const auto &i : items)
            i->print(out, bindings);
    }

    void add(nodePtr ptr)
    {
        items.push_back(ptr);
    };
};

#endif // STANDARD_LIST_H
