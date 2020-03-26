#if !defined(MIPS_H)
#define MIPS_H

// MIPS Helper functions
// - implement different MIPS instructions
// - called inside print functions of Nodes

#include <string>

using namespace std;

class Mips //call like this:  "Mips::move(...);"
{
public:
    string move(string r1, string r2)
    {
        return "\tmove\t" + r1 + "," + r2;
    };
};

#endif // MIPS_H