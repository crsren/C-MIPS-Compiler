#ifndef DECLARATOR_H
#define DECLARATOR_H

#include "../helpers.h"

class Declarator //this is used as varDeclarator and as the base class for fnDeclarator
{
protected:
    const std::string identifier;

public:
    Declarator(const std::string &s) : identifier(s){}

    const std::string getIdentifier() const
    {
        return identifier;
    }
};

//TODO: class ArrayDeclarator : public Declarator

class InitDeclarator : public Node
{
    std::string specifierType = ""; // single specifier for now
    Declarator* declarator;
    nodePtr initializer;

public:
    InitDeclarator(Declarator *d, nodePtr i) : declarator(d), initializer(i){};
    InitDeclarator(Declarator *d) : declarator(d), initializer(nullptr){};

    ~InitDeclarator()
    {
        delete declarator;
        delete initializer;
    }

    void print(std::ostream &out, LocalVariableBindings &bindings) const override;

    void setType(std::string specifier) //set by declaration
    {
        specifierType = specifier;
    };
};

class InitDeclaratorList : public Node
{
    // std::string specifierType = ""; // single specifier for now
    std::list<InitDeclarator *> initDeclaratorList;

public:
    InitDeclaratorList(InitDeclarator *first)
    {
        initDeclaratorList.push_back(first);
    }

    void setType(std::string specifier) //set by declaration
    {
        // specifierType = specifier;
        for (auto &initDeclarator : initDeclaratorList)
            initDeclarator->setType(specifier);
    };

    void add(InitDeclarator *first)
    {
        initDeclaratorList.push_back(first);
    }
};

#endif // DECLARATOR_H
