#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Context/bindings.h"

class Node;
typedef const Node *nodePtr;

class Node
{
public:
    virtual ~Node(){};
    virtual void print(std::ostream &out, LocalVariableBindings *bindings) const = 0;
    //const = 0;
};

#endif // NODE_H
