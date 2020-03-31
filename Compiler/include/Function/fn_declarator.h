#ifndef FN_DECLARATOR_H
#define FN_DECLARATOR_H

#include "../helpers.h"
#include "../Declaration/declarators.h"

class ParameterDeclaration
{
    const std::string specifier; // f.e. int
    Declarator *declarator;      // not necessary! could be int foo(int, int);

public:
    ParameterDeclaration(std::string s, Declarator *d) : specifier(s), declarator(d){};

    Declarator *getDeclarator()
    {
        return declarator;
    }

    std::string getSpecifier()
    {
        return specifier;
    }

    ~ParameterDeclaration()
    {
        delete declarator;
    }
};

class ParameterList
{
    std::vector<ParameterDeclaration *> pList;

public:
    ParameterList(ParameterDeclaration *parameter)
    {
        pList.push_back(parameter);
    };

    void add(ParameterDeclaration *parameter)
    {
        pList.push_back(parameter);
    };

    std::vector<ParameterDeclaration *> getItems()
    {
        return pList;
    };
};

class FnDeclarator : public Declarator
{
    ParameterList *parameterList; //parameter

public:
    FnDeclarator(Declarator *declarator, ParameterList *l = nullptr) : Declarator(declarator->getIdentifier(), true), parameterList(l){};

    ParameterList *getParameterList()
    {
        return parameterList; // use: this->getParameterList()->getIdentifiers(); in fnDefinition
    }

    ~FnDeclarator()
    {
        delete parameterList;
    };
};

#endif // FN_DECLARATOR_H
