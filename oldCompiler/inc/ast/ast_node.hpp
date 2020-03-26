#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node
{
public:
    virtual ~Node(){}
    virtual void printMIPS(std::ostream &out) const = 0; //printing MIPS equivalent
};

#endif // NODE_HPP
