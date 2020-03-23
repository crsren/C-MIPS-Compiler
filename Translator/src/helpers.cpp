#include "helpers.h"

std::ostream &operator<<(std::ostream &os, const Indent &indent)
{
    os << std::string(indent.count, ' ');
    return os;
};

std::ostream &operator<<(std::ostream &os, const Global &global)
{
    for (auto &v : global.variables)
    {
        os << Indent::instance() << "global " << v << '\n';
    }

    return os;
};