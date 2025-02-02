#ifndef LIST_H
#define LIST_H

#include <list>
#include <string>
#include "node.h"
#include "statements.h"

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
        std::string seperator = "";
        for (const auto i : pList)
        {
            out << seperator;
            seperator = ",";
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
            if (i != nullptr)
            {
                i->print(out);
                out << '\n';
            }
        }
    };

    virtual void add(nodePtr ptr) const override
    {
        sList.push_back(ptr);
    }
};

class transUnitList : public Node
{
private:
    mutable std::list<nodePtr> tList;

public:
    transUnitList(nodePtr first)
    {
        tList.push_back(first);
    }

    void print(std::ostream &out) const override
    {
        for (const auto i : tList)
        {
            i->print(out);
            //out << '\n';
        }
    }

    void add(nodePtr ptr) const override
    {
        tList.push_back(ptr);
    }
};

#endif // LIST_H
