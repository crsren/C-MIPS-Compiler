#if !defined(LIST_H)
#define LIST_H

#include "AST.h"
#include <list>

typedef const Node *nodePtr;

class paramList : public Node
{
private:
    mutable std::list<nodePtr> pList;

public:
    paramList(nodePtr first)
    {
        pList.push_back(first);
    };

    virtual void print(std::ostream &out) const override
    {
        unsigned char seperator = 0;
        for (const auto i : pList)
        {
            out << seperator;
            seperator = ',';
            i->print(out);
        }
    };

    virtual void add(nodePtr ptr) const override
    {
        pList.push_back(ptr);
    }
};

class statementList : public Node
{
private:
    mutable std::list<nodePtr> sList;

public:
    statementList(nodePtr first)
    {
        sList.push_back(first);
    }

    virtual void print(std::ostream &out) const override
    {
        for (const auto i : sList)
        {
            i->print(out);
            out << 'n';
        }
    };

    virtual void add(nodePtr ptr) const override
    {
        sList.push_back(ptr);
    }
};

#endif // LIST_H
