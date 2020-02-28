#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <iostream>
#include <string>

using namespace std;

class Identifier : public Expression
{
private:
    string ID;

public:
    Identifier(const string &id) : ID(id){};

    const string getID() { return ID; };
};

#endif // PRIMITIVES_H
