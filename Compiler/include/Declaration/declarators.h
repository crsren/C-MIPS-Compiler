#ifndef DECLARATORS_H
#define DECLARATORS_H

#include "../helpers.h"
#include "Expressions/primitives.h"

//TODO: class ArrayDeclarator : public Declarator

class Declarator //this is used as varDeclarator and as the base class for fnDeclarator
{
protected:
    Identifier *identifier;

public:
    const bool isFunction;
    Declarator(Identifier *s, bool isF) : identifier(s), isFunction(isF) {}

    Identifier *getIdentifier() const
    {
        return identifier;
    }

    virtual ~Declarator()
    {
        delete identifier;
    }
};

// Not fully implemented
class ArrayDeclarator : public Declarator
{
    nodePtr constantExpr;

public:
    std::vector<std::string> content;
    ArrayDeclarator(const Declarator *declarator, nodePtr constantExpr = nullptr) : Declarator(declarator->getIdentifier(), false)
    {
        std::string name = identifier->getName();

        // Only works for numerical indexes
        const Constant *constantVal;
        if (constantExpr)
            constantVal = dynamic_cast<const Constant *>(constantExpr);
        int arraySize = constantVal->getValue();

        for (int i = 0; i < arraySize; i++)
        {
            content.push_back(name + std::to_string(i));
        }
    }

    ~ArrayDeclarator()
    {
        delete constantExpr;
    }
};

#endif //DECLARATORS_H
