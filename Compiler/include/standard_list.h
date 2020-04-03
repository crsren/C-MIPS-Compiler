#ifndef STANDARD_LIST_H
#define STANDARD_LIST_H

#include "helpers.h"

// https://stackoverflow.com/questions/31513730/building-a-linked-list-in-yacc-with-left-recursive-grammar

class List : public Node
{
    std::vector<nodePtr> items;

public:
    List(nodePtr first)
    {
        items.push_back(first);
    };

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "List::print\tSTART\n";

        std::cerr << GlobalIndent::instance().globalIndent << "for (evey item in the list)\n";
        std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t";
        for (const auto &i : items)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current item\n";
            if (i)
                i->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
        }
        GlobalIndent::instance().globalIndent = oldGlobalIndent;

        std::cerr << GlobalIndent::instance().globalIndent << "List::print\tEND\n";
    }

    void add(nodePtr ptr)
    {
        items.push_back(ptr);
    };

    std::vector<nodePtr> &getItems()
    {
        return items;
    }

    int getSize() const
    {
        return items.size();
    }
};

#endif // STANDARD_LIST_H
