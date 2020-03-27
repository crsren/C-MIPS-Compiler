#if !defined(LIST_H)
#define LIST_H

#include "node.h"

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

    virtual void print(std::ostream &out, !!!) const override
    {
        for (nodePtr i : items)
            i->print(out, !!!);
    }

    virtual void add(nodePtr ptr)
    {
        items.push_back(ptr);
    };
};

#endif // LIST_H
