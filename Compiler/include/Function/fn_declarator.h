#ifndef FN_DECLARATOR_H
#define FN_DECLARATOR_H

#include "../helpers.h"
#include "../Declaration/declarators.h"

class ParameterDeclaration
{
    const std::string specifier;  // f.e. int
    const Declarator *declarator; // not necessary! could be int foo(int, int);

public:
    ParameterDeclaration(const std::string s, const Declarator *d = nullptr) : specifier(s), declarator(d){};

    const Declarator *getDeclarator() const
    {
        return declarator;
    }

    std::string getSpecifier() const
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
    std::vector<const ParameterDeclaration *> pList;

public:
    ParameterList(const ParameterDeclaration *parameter)
    {
        pList.push_back(parameter);
    };

    void add(const ParameterDeclaration *parameter)
    {
        pList.push_back(parameter);
    };

    std::vector<const ParameterDeclaration *> getItems()
    {
        return pList;
    };
};

class FnDeclarator : public Declarator
{
    ParameterList *parameterList; //parameter

public:
    FnDeclarator(const Declarator *declarator, ParameterList *l = nullptr) : Declarator(declarator->getIdentifier(), true), parameterList(l){};

    ParameterList *getParameterList() const
    {
        return parameterList; // use: this->getParameterList()->getIdentifiers(); in fnDefinition
    }

    ~FnDeclarator()
    {
        delete parameterList;
    };
};

#endif // FN_DECLARATOR_H
