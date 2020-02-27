#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <fstream>
#include <map>

#include <memory>

class Node;

typedef const Node* NodePtr;

class Node
{
public:
    virtual ~Node()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(std::ofstream &file) const = 0;

};

#endif
