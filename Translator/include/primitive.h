#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <iostream>
#include <string>
#include "node.h"

using namespace std;

class Primitive : public Node
{
private:
    string content;

public:
    Primitive(const string &in) : content(in){};
    //just in case:
    Primitive(const int &in) : content(to_string(in)){};

    virtual void print(std::ostream &out) const override
    {
        out << content;
    };

    virtual std::string getContent() const override
    {
        return content;
    }
};

class TypeSpecifier : public Node
{
    virtual void print(std::ostream &out) const override{};
};

#endif // PRIMITIVES_H
