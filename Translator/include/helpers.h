#ifndef HELPERS_H
#define HELPERS_H

// dealing with indent and global variable

#include <string>
#include <vector>
#include <iostream>

//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class Indent
{
    int count;

public:
    static Indent &instance()
    {
        static Indent instance; //Insantiated on first use
        return instance;
    };
    //out << Indent::instance() << ...;

    Indent() : count(0){};

    int getCount()
    {
        return count;
    };

    void operator++(int)
    {
        count++;
    };

    void operator--(int)
    {
        count--;
    };

    // overloading insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Indent &indent);
};

class Global
{
    std::vector<std::string> variables;

public:
    static Global &instance()
    {
        static Global instance; //Insantiated on first use
        return instance;
    };

    void add(const std::string &s)
    {
        variables.push_back(s);
    };

    // overloading insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Global &global);
};

#endif // HELPERS_H
