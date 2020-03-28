#ifndef MIPS_H
#define MIPS_H

// MIPS Helper functions
// - implement different MIPS instructions
// - called inside print functions of Nodes

#include <string>

class Mips //call like this:  "Mips::move(...);"
{
public:
    static std::string branch(std::string label)
    {
        std::string tmp = "\tb\t$" + label + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string beq(int reg1, int reg2, std::string label)
    {
        // need $ for label?
        std::string tmp = "\tbeq\t$" + std::to_string(reg1) + ",$" + std::to_string(reg2) + ", " + label + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string move(int regNum1, int regNum2)
    {
        return "\tmove\t$" + std::to_string(regNum1) + ",$" + std::to_string(regNum2) + "\n";
    }

    static std::string load_word(int regNum, int addressOffset, bool fromStack)
    {
        std::string out = "\tlw\t$" + std::to_string(regNum) + ",-" + std::to_string(addressOffset);
        if (fromStack)
        {
            out += "($sp)\n";
        }
        else
        {
            out += "($fp)\n";
        }

        return out;
    }

    static std::string store_word(int regNum, int addressOffset, bool toStack)
    {
        std::string out = "\tsw\t$" + std::to_string(regNum) + ",-" + std::to_string(addressOffset);
        if (toStack)
        {
            out += "($sp)\n";
        }
        else
        {
            out += "($fp)\n";
        }

        return out;
    }

    static std::string addu(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\taddu\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string subu(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tsubu\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string mul(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tmul\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string div_quotient(int quotientRegNum, int dividentRegNum, int divisorRegNum)
    {
        std::string out = "\tdiv\t$" + std::to_string(dividentRegNum) + ",$" + std::to_string(divisorRegNum) + "\n";
        out += "\tmflo\t$" + std::to_string(quotientRegNum) + "\n";
        return out;
    }

    static std::string div_remainder(int remainderRegNum, int dividentRegNum, int divisorRegNum)
    {
        std::string out = "\tdiv\t$" + std::to_string(dividentRegNum) + ",$" + std::to_string(divisorRegNum) + "\n";
        out += "\tmfhi\t$" + std::to_string(remainderRegNum) + "\n";
        return out;
    }

    static std::string slt(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tslt\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string sltu(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tsltu\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string slti(int destRegNum, int sourceRegNum, int immediate)
    {
        return "\tslti\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum) + "," + std::to_string(immediate) + "\n";
    }

    static std::string sltiu(int destRegNum, int sourceRegNum, int immediate)
    {
        return "\tsltiu\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum) + "," + std::to_string(immediate) + "\n";
    }

    static std::string xor_(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\txor\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string xori(int destRegNum, int sourceRegNum, int immediate)
    {
        return "\txori\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum) + "," + std::to_string(immediate) + "\n";
    }

    static std::string and_(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tand\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string andi(int destRegNum, int sourceRegNum, int immediate)
    {
        return "\tandi\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum) + "," + std::to_string(immediate) + "\n";
    }

    static std::string or_(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tor\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string ori(int destRegNum, int sourceRegNum, int immediate)
    {
        return "\tori\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum) + "," + std::to_string(immediate) + "\n";
    }

    static std::string sll(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tsll\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string sra(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tsra\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string jump(int r1 = 31) //default jump to return address
    {
        std::string tmp = "\tj\t$" + std::to_string(r1) + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string jal(std::string name)
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