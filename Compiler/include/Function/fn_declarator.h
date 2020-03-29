#ifndef FN_DECLARATOR_H
#define FN_DECLARATOR_H

#include "../helpers.h"
#include "../Declaration/declarators.h"

class FnDeclarator : public Declarator
{
private:
    nodePtr identifier;    // function identifier
    nodePtr parameterList; //parameter

public:
    FnDeclarator(nodePtr d, nodePtr l = nullptr) : identifier(d), parameterList(l){};

    virtual void print(std::ostream &out, VariableBindings &bindings) const override; //TODO: implement

    ~FnDeclarator()
    {
        delete identifier;
        delete parameterList;
    };
};

class ParameterDeclaration : public Node
{
public:
    const std::string specifier; // f.e. int
    Declarator *declarator;      // not necessary! could be int foo(int, int);

    ParameterDeclaration(std::string s, Declarator *d) : specifier(s), declarator(d){};

    void print(std::ostream &out, VariableBindings &bindings) const override; //TODO: Implement
    // if declarator != nullptr; get declarator->identifier, add to local bindings;

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

    std::vector<std::string> &getIdentifiers()
    {
        std::vector<std::string> identifierVector;

        for (const auto &parameter : pList)
            identifierVector.push_back(parameter->declarator->getIdentifier());

        return identifierVector;
    };
};

#endif // FN_DECLARATOR_H
