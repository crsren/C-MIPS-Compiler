#ifndef HELPERS_H
#define HELPERS_H

// This header includes library and helper classes/functions used across the AST

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "node.h"
#include "mips.h"
#include "standard_list.h"
#include "Context/bindings.h"

// Singletons
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

// Guarantees unique labeling
class Label // usage: Label::instance().uniquify("string");
{
    int count;

public:
    static Label &instance()
    {
        static Label instance; //Insantiated on first use
        return instance;
    }

    Label() : count(0){};

    std::string uniquify(std::string base)
    { // extra "_" before to ensure label is not used as variable
        return "-" + base + "_" + std::to_string(count++);
    };
};

#endif // HELPERS_H
