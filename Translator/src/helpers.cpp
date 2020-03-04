#include "helpers.h"

std::ostream &operator<<(std::ostream &os, const Indent &indent)
{
    os << indent();
    return os;
};