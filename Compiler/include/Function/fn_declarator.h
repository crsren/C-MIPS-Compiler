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
    nodePtr specifier;      // f.e. int
    Declarator *declarator; // not necessary! could be int foo(int, int);

    ParameterDeclaration(nodePtr s, nodePtr d) : specifier(s), declarator(d){};

    void print(std::ostream &out, VariableBindings &bindings) const override; //TODO: Implement
    // if declarator != nullptr; get declarator->identifier, add to local bindings;

    ~ParameterDeclaration()
    {
        delete specifier;
        delete declarator;
    }
}

/// USING LIST FOR NOW
// class ParameterList : public Node
// {
//     std::list<nodePtr> pList;

// public:
//     ParameterList(nodePtr parameter)
//     {
//         pList.push_back(parameter);
//     };

//     void add(nodePtr parameter)
//     {
//         pList.push_back(parameter);
//     };
// }

#endif // FN_DECLARATOR_H
