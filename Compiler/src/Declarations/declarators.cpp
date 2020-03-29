#include "Declarations/declarators.h"

void InitDeclarator::print(out, bindings)
{
    std::string identifier = declarator->getIdentifier();
    // this.specifierType is the type (got this from declaration class before this print function is being called )

    if
        specifierType is int :

            if (bindings /* == nullptr*/) // -> global scope

            if (initializer /* == nullptr */) // -> declare as zero
            else initializer->print           // -> declare as value in $2
            else                              // -> local scope
            allocate space on the stack
                initializer->print

            else if specifierType is void
};