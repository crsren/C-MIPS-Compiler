#ifndef NODE_H
#define NODE_H

#include "helpers.h"
#include <iostream>

class Node
{
public:
    virtual ~Node(){};
    virtual void print(std::ostream &out) const = 0; //printing python equivalent
    virtual std::string getContent() const = 0;
};

#endif // NODE_H
