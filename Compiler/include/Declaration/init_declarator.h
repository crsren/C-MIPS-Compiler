#if !defined(INIT_DECLARATOR_h)
#define INIT_DECLARATOR_h

#include "helpers.h"
#include "Function/fn_declarator.h"

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

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;

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

#endif // INIT_DECLARATOR_h
