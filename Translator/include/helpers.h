#if !defined(HELPERS_H)
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
        static Indent instance;
        return instance;
    };
    //out << Indent::instance() << ...;

    Indent() : count(0)
    {
        std::cerr << "Indent initiated." << '\n';
    };

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

    std::string operator()() const
    {
        return std::string(count, ' ');
    };

    friend std::ostream &operator<<(std::ostream &os, const Indent &indent);
};

//implement
class Global
{
    std::vector<std::string> variables;

public:
    static Global &instance()
    {
        static Global instance;
        return instance;
    };

    void add(const std::string &s)
    {
        variables.push_back(s);
    };

    friend std::ostream &operator<<(std::ostream &os, const Global &global);
};

#endif // HELPERS_H
