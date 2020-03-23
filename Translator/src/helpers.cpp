#include "helpers.h"

std::ostream &operator<<(std::ostream &os, const Indent &indent)
{
    os << std::string(indent.count, '\t');
    return os;
};

std::ostream &operator<<(std::ostream &os, const Global &global)
{
    if (global.variables.size() > 0)
    {
        Indent::instance()++;
        for (auto &v : global.variables)
        {
            os << Indent::instance() << "global " << v << '\n';
        }
        Indent::instance()--;
    }

    return os;
};