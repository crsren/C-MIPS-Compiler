#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node
{
public:
    virtual ~Node(){};
    virtual void print(std::ostream &out, !!!) const { std::cerr << "Unimplemented node.\n"; };
    //const = 0;
};

const Node *nodePtr;

#endif // NODE_H
