#ifndef DECLARATOR_H
#define DECLARATOR_H

#include "../helpers.h"
#include "Expressions/primitives.h"

class Declarator //this is used as varDeclarator and as the base class for fnDeclarator
{
protected:
    Identifier *identifier;

public:
    const bool isFunction;
    Declarator(Identifier* s, bool isF) : identifier(s), isFunction(isF) { }

    Identifier *getIdentifier() const
    {
        return identifier;
    }

    virtual ~Declarator()
    {
        delete identifier;
    }
};

//TODO: class ArrayDeclarator : public Declarator

class InitDeclarator : public Node
{
    std::string specifierType = ""; // single specifier for now
    const Declarator *declarator;
    nodePtr initializer;

public:
    InitDeclarator(const Declarator *d, nodePtr i) : declarator(d), initializer(i){};
    InitDeclarator(const Declarator *d) : declarator(d), initializer(nullptr){};

    ~InitDeclarator()
    {
        delete declarator;
        delete initializer;
    }

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;

    void setType(std::string specifier) //set by declaration
    {
        specifierType = specifier;
    };
};

class InitDeclaratorList : public Node
{
    // std::string specifierType = ""; // single specifier for now
    std::list<InitDeclarator *> items;

public:
    InitDeclaratorList(InitDeclarator *first)
    {
        items.push_back(first);
    }

    void print(std::ostream &out, LocalVariableBindings *bindings) const override
    {
        std::cerr << GlobalIndent::instance().globalIndent << "for (evey initDeclarator in the list)\n";
        std::string oldGlobalIndent = GlobalIndent::instance().globalIndent;
        GlobalIndent::instance().globalIndent += "\t";
        for (const auto &initDeclarator : items)
        {
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n";
            std::cerr << GlobalIndent::instance().globalIndent << "Print the current initDeclarator\n";
            initDeclarator->print(out, bindings);
            std::cerr << GlobalIndent::instance().globalIndent << "**************************\n\n";
        }
        GlobalIndent::instance().globalIndent = oldGlobalIndent;
    }

    void setType(std::string specifier) //set by declaration
    {
        // specifierType = specifier;
        for (auto &initDeclarator : items)
            initDeclarator->setType(specifier);
    };

    void add(InitDeclarator *first)
    {
        items.push_back(first);
    }
};

#endif // DECLARATOR_H
