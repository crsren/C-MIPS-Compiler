#ifndef MIPS_H
#define MIPS_H

// MIPS Helper functions
// - implement different MIPS instructions
// - called inside print functions of Nodes

#include <string>

class Mips //call like this:  "Mips::move(...);"
{
public:
    static std::string load_immediate(int toReg, int value)
    {
        return "\tli\t$" + std::to_string(toReg) + ", " + std::to_string(value) + "\n";
    }

    static std::string load_address(int toReg, std::string adressLabel)
    {
        return "\tla\t$" + std::to_string(toReg) + ", " + adressLabel + "\n";
    }

    static std::string branch(const std::string &label)
    {
        // need $ for label?
        std::string tmp = "\tb\t" + label + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string beq(int reg1, int reg2, const std::string &label)
    {
        // need $ for label?
        std::string tmp = "\tbeq\t$" + std::to_string(reg1) + ",$" + std::to_string(reg2) + ", " + label + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string bne(int reg1, int reg2, const std::string &label)
    {
        // need $ for label?
        std::string tmp = "\tbne\t$" + std::to_string(reg1) + ",$" + std::to_string(reg2) + ", " + label + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string move(int toReg, int fromReg)
    {
        return "\tadd\t$" + std::to_string(toReg) + ",$" + std::to_string(fromReg) + ",$0\n";
    }

    static std::string load_word(int regNum, int addressOffset, bool fromStack) //local
    {
        std::string out = "";
        if (addressOffset >= 0)
        {
            out += "\tlw\t$" + std::to_string(regNum) + ",-" + std::to_string(addressOffset);
            if (fromStack) //using stack pointer
            {
                out += "($sp)\n";
            }
            else //using frame pointer
            {
                out += "($fp)\n";
            }
        }
        else if (addressOffset > -5)
        {
            out += Mips::move(regNum, 3 - addressOffset);
        }
        else
        {
            out += "\tlw\t$" + std::to_string(regNum) + "," + std::to_string(-addressOffset-1+16);
            if (fromStack) //using stack pointer
            {
                out += "($sp)\n";
            }
            else //using frame pointer
            {
                out += "($fp)\n";
            }
        }

        return out;
    }

    static std::string load_global_word(int regNum, std::string variableIdentifier)
    {
        std::string out = "\tla\t$1," + variableIdentifier + "\n";
        out += "\tlw\t$" + std::to_string(regNum) + ",0($1)\n";
        return out;
    }

    static std::string load_word_reg(int destRegNum, int addressOffset, int addressRegNum)
    {
        std::string out = "\tlw\t$" + std::to_string(destRegNum) + "," + std::to_string(addressOffset) + "($" + std::to_string(addressRegNum) + ")\n";
        return out;
    }

    static std::string store_word(int regNum, int addressOffset, bool toStack)
    {
        std::string out = "";
        if (addressOffset >= 0)
        {
            out += "\tsw\t$" + std::to_string(regNum) + ",-" + std::to_string(addressOffset);
            if (toStack)
            {
                out += "($sp)\n";
            }
            else
            {
                out += "($fp)\n";
            }
        }
        else if (addressOffset > -5)
        {
            out += Mips::move(3 - addressOffset, regNum);
        }
        else
        {
            out += "\tsw\t$" + std::to_string(regNum) + "," + std::to_string(-addressOffset-1+16);
            if (toStack)
            {
                out += "($sp)\n";
            }
            else
            {
                out += "($fp)\n";
            }
        }
        

        return out;
    }

    static std::string store_global_word(int regNum, std::string variableIdentifier)
    {
        std::string out = "\tla\t$1," + variableIdentifier + "\n";
        out += "\tsw\t$" + std::to_string(regNum) + ",0($1)\n";
        return out;
    }

    static std::string store_word_reg(int sourceRegNum, int addressOffset, int addressRegNum)
    {
        std::string out = "\tsw\t$" + std::to_string(sourceRegNum) + "," + std::to_string(addressOffset) + "($" + std::to_string(addressRegNum) + ")\n";
        return out;
    }

    static std::string add_(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tadd\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string addu(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\taddu\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string addi(int destRegNum, int sourceRegNum, int immediate)
    {
        return "\taddi\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum) + "," + std::to_string(immediate) + "\n";
    }

    static std::string addiu(int destRegNum, int sourceRegNum, int immediate)
    {
        return "\taddiu\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum) + "," + std::to_string(immediate) + "\n";
    }

    static std::string sub_(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tsub\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
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

    static std::string nor_(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tnor\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string sllv(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tsllv\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string srav(int destRegNum, int sourceRegNum1, int sourceRegNum2)
    {
        return "\tsrav\t$" + std::to_string(destRegNum) + ",$" + std::to_string(sourceRegNum1) + ",$" + std::to_string(sourceRegNum2) + "\n";
    }

    static std::string jump_register(int regNum) //default jump to return address
    {
        std::string tmp = "\tjr\t$" + std::to_string(regNum) + "\n";
        tmp += "\tnop\n";
        return tmp;
    }

    static std::string jal(const std::string &label)
    {
        return "\tjal\t" + label + "\n";
    }

    static std::string segment_text()
    {
        return ".text\n";
    }

    static std::string segment_data()
    {
        return ".data\n";
    }

    static std::string new_label(const std::string &label)
    {
        return label + ":\n";
    }

    static std::string word_data(const std::string &identifier, int value)
    {
        return identifier + ":\n\t.word\t" + std::to_string(value) + "\n";
    }

    static std::string tag_global(const std::string &tag)
    {
        return ".globl\t" + tag + "\n";
    }

    static std::string function_prologue(const std::string &functionIdentifier)
    {
        std::string out = "";
        out += Mips::segment_text();
        out += Mips::tag_global(functionIdentifier);
        out += Mips::new_label(functionIdentifier);
        out += Mips::addi(29, 29, -4);
        out += Mips::store_word(31, 0, true); // $31 = $ra
        out += Mips::store_word(30, 4, true); // $30 = $fp
        out += Mips::move(30, 29);
        return out;
    }

    static std::string function_epilogue()
    {
        std::string out = "";
        out += Mips::load_word(31, 0, false);
        out += Mips::load_word(30, 4, false);
        out += Mips::move(29, 30);
        out += Mips::jump_register(31);
        return out;
    }
};

#endif // MIPS_H