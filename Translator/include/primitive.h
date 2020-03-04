#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <iostream>
#include <string>
#include "AST.h"

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
    }
}

// class Identifier : public Node
// {
// private:
//     string content;

// public:
//     Identifier(const string &in) : content(in){};

//     virtual void print(std::ostream &out) const override
//     {
//         out << content;
//     }
// };

// class Constant : public Node
// {
// private:
//     int content;

// public:
//     Constant(const int &val) : content(val){};

//     virtual void print(std::ostream &out) const override
//     {
//         out << content;
//     }
// };

#endif // PRIMITIVES_H
