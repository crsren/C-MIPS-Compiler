#ifndef MIPS_H
#define MIPS_H

// MIPS Helper functions
// - implement different MIPS instructions
// - called inside print functions of Nodes

#include <string>

class Mips //call like this:  "Mips::move(...);"
{
public:
    static std::string move(int registerNumber1, int registerNumber2)
    {
        return "\tmove\t$" + std::to_string(registerNumber1) + "," + "$" + std::to_string(registerNumber1) + "\n";
    };

    static std::string jump(std::string r1 = "$31") //default jump to return address
    {
        std::string tmp = "\tj\t" + r1 + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string jump_to_label(std::string name)
    {
        return "\tjal\t" + name + "\n";
    }

    static std::string segment_text()
    {
        return ".text\n";
    }

    static std::string segment_data()
    {
        return ".data\n";
    }

    static std::string label(std::string label)
    {
        return label + ":\n";
    }

    static std::string tag_global(std::string tag)
    {
        return ".globl" + tag + "\n";
    }
};

#endif // MIPS_H