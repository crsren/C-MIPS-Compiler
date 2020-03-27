#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "helpers.h"

class Node;
typedef const Node *nodePtr;

class Node
{
public:
    virtual ~Node(){};
    virtual void print(std::ostream &out, VariableBindings bindings) const { std::cerr << "Unimplemented node.\n"; };
    //const = 0;
};

#endif // NODE_H
