#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "node.h"

class Node
{
public:
    virtual ~Node(){};
    virtual void print(std::ostream &out) const = 0; //printing python equivalent
    virtual std::string getContent() const { return ""; };
    virtual void add(const Node *ptr) const { return; };
};

#endif // NODE_H
