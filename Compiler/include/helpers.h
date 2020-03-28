#ifndef HELPERS_H
#define HELPERS_H

// This header includes library and helper classes/functions used across the AST

#include "node.h"
#include "mips.h"
#include "Context/bindings.h"

#include <iostream>
#include <string>

// Singletons
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

// Guarantees unique labeling
class Label
{
    int count;

public:
    static Label &instance()
    {
        static Label instance; //Insantiated on first use
        return instance;
    }

    Label() : count(0){};

    std::string uniquefy(std::string base)
    {
        return base + "_" + std::to_string(count++);
    };
};

#endif // HELPERS_H
