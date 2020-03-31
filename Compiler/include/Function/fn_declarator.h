#ifndef FN_DECLARATOR_H
#define FN_DECLARATOR_H

#include "../helpers.h"
#include "../Declaration/declarators.h"

class FnDeclarator : public Declarator
{
private:
    ParameterList *parameterList; //parameter

public:
    FnDeclarator(ParameterList *l = nullptr) : parameterList(l), isFunction(true) {};

    virtual void print(std::ostream &out, LocalVariableBindings &bindings) const override;

    ~FnDeclarator()
    {
        delete parameterList;
    };

    ParameterList *getParameterList()
    {
        return parameterList; // use: this->getParameterList()->getIdentifiers(); in fnDefinition
    }
};

class ParameterDeclaration
{    
    const std::string specifier; // f.e. int
    Declarator *declarator;      // not necessary! could be int foo(int, int);

public:

    ParameterDeclaration(std::string s, Declarator *d) : specifier(s), declarator(d){};

    Declarator* getDeclarator() {
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

class ParameterList : public Node
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

    std::list<const ParameterDeclaration *> getParameterList()
    {
        return pList;
    };
};

#endif // FN_DECLARATOR_H
