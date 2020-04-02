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

#endif //DECLARATORS_H
