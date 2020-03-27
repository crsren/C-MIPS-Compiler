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
    static string move(string r1, string r2)
    {
        return "\tmove\t" + r1 + "," + r2;
    };

    static string jump(string r1 = "$31") //default jump to return address
    {
        string tmp = "\tj\t" + r1 + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static string jump_to_label(string name)
    {
        return "\tjal\t" + name + "\n";
    }

    static string segment_text()
    {
        return ".text\n";
    }

    static string segment_data()
    {
        return ".data\n";
    }

    static string label(string label)
    {
        return label + ":\n";
    }

    static string tag_global(string tag)
    {
        return ".globl" + tag + "\n";
    }
};

#endif // MIPS_H