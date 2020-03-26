#if !defined(MIPS_H)
#define MIPS_H

// Functions with return type string that implement different MIPS instructions
// to be called inside print functions of Nodes

#include <string>

using namespace std;

class Mips
{
public:
    string move(string r1, string r2)
    {
        return "\tmove\t" + r1 + "," + r2;
    };
}

#endif // MIPS_H