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
        std::cerr << "List::print\tSTART\n";

        std::cerr << "for (evey item in the list)\n";
        for (const auto &i : items)
        {
            std::cerr << "\t**************************\n";
            std::cerr << "\tPrint the current item\n";
            i->print(out, bindings);
            std::cerr << "\t**************************\n\n";
        }

        std::cerr << "List::print\tSTART\n";
    }

    void add(nodePtr ptr)
    {
        items.push_back(ptr);
    };
};

#endif // STANDARD_LIST_H
