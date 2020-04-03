#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>

enum PrimitiveDataTypeCode
{
    _INTEGER,
    _DOUBLE,
    _FLOAT,
    _CHAR,
    _UNSIGNED,
    _VOID
    // ,
    // ENUMERATION
};

// struct Enumeration
// {
//     std::unordered_map<std::string, int> enumerationMap;
//     int enumeratedString;
// };

// class Pointer
// {
//     PrimitiveDataType type;
// };

// class Structure
// {
//     std::vector<PrimitiveDataType> vectorOfMemberVariables;
// };

class Array
{
private:
    PrimitiveDataTypeCode arrayDataTypeCode;
    std::vector<int> arrayDimensionalSizes;

public:
    int nDimensions_to_1Dimensions(const std::vector<int> &arrayIndices)
    {
        int offset = 0;
        for (int dimension = 0; dimension < arrayIndices.size(); dimension++)
        {
            offset += arrayIndices[dimension] * arrayDimensionalSizes[dimension];
        }
        return offset;
    }

    void setArrayDataTypeCode(const PrimitiveDataTypeCode &dataTypeCode)
    {
        arrayDataTypeCode = dataTypeCode;
    }

    void setArrayDimensionalSizes(const std::vector<int> dimensionalSizes)
    {
        arrayDimensionalSizes = dimensionalSizes;
    }

    const std::vector<int> getArrayDimensionalSizes() const
    {
        return arrayDimensionalSizes;
    }

    const int getArrayDataTypeCode() const
    {
        return arrayDataTypeCode;
    }
};

struct Function
{
    PrimitiveDataTypeCode functionReturnDataTypeCode;

    bool return_type_is_pointer;

    int numberOfParameters; // assuming all int
};

// struct containing information on the variable declaration
struct Variable
{
    PrimitiveDataTypeCode variableDataTypeCode;

    Array arrayVariable;

    // the addressOffset is the value that must be subtracted from the stack pointer
    // to evaluate the memory location of the variable
    //
    // if the addressOffset is negative in the range [-4, -1] then taking |addressOffset| + 3
    // represnts the "argument register" number ($4, $5, $6, $7) in which the variable is stored
    int addressOffset;

    bool is_pointer;

    bool is_array;
};

class GlobalVariableBindings // usage: GlobalBindings::instance().<function>();
{
    // note that this map holds the identifiers and the data of the global
    // variables
    //
    // ALSO note that in MIPS the variable identifiers correspond to the actual
    // memory address of the global variable
    //
    // note that it is static since the global variables are shared by every
    // local scope and thus, by every instance of the VariableBindings class
    std::unordered_map<std::string, Variable> globalBindings;

    // note that this map holds the identifiers and the data of the functions
    //
    // ALSO note that in MIPS the function identifiers correspond to the actual
    // memory address of the starting point of the functions
    //
    // note that it is static since the functions are "global" in the sense that
    // are shared by every local scope and thus, by every instance of the VariableBindings class
    std::unordered_map<std::string, Function> functionBindings;

    // the currentGlobalExpressionAddressOffset is the value that must be subtracted from
    // the stack pointer to get the memory location of the current intermediate stored
    // expression
    int currentGlobalExpressionAddressOffset;

public:
    GlobalVariableBindings() : currentGlobalExpressionAddressOffset(0) {}

    static GlobalVariableBindings &instance()
    {
        static GlobalVariableBindings instance; //Instantiated on first use
        return instance;
    }

    void insertGlobalVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, bool isPointer)
    {
        Variable var;
        var.addressOffset = -1;
        var.is_array = false;
        var.is_pointer = isPointer;
        var.variableDataTypeCode = dataTypeCode;
        globalBindings.insert(std::make_pair(id, var));
    }

    bool globalVariableBindingExists(const std::string &id) const
    {
        if (globalBindings.find(id) == globalBindings.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool globalVariableIsArray(const std::string &id)
    {
        auto variableBinding = globalBindings.find(id);
        return (*variableBinding).second.is_array;
    }

    bool globalVariableIsPointer(const std::string &id)
    {
        auto variableBinding = globalBindings.find(id);
        return (*variableBinding).second.is_pointer;
    }

    bool functionReturnsPointer(const std::string &id)
    {
        auto functionBinding = functionBindings.find(id);
        return (*functionBinding).second.return_type_is_pointer;
    }

    void insertGlobalArrayVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, const std::vector<int> arrayDimensionSizes_i)
    {
        Variable var;
        var.addressOffset = -1;
        var.is_array = true;
        var.is_pointer = true;

        int arraySize = 1;
        for (int i = 0; i < arrayDimensionSizes_i.size(); i++)
        {
            arraySize *= arrayDimensionSizes_i[i];
        }
        arraySize *= 4;
        if (dataTypeCode == _DOUBLE)
        {
            arraySize *= 2;
        }

        Array varArray;
        varArray.setArrayDataTypeCode(dataTypeCode);
        varArray.setArrayDimensionalSizes(arrayDimensionSizes_i);
        var.arrayVariable = varArray;

        globalBindings.insert(std::make_pair(id, var));
    }

    void insertFunctionBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, int paramNumber, bool returnsPointer)
    {
        Function func;
        func.functionReturnDataTypeCode = dataTypeCode;
        func.numberOfParameters = paramNumber;
        func.return_type_is_pointer = returnsPointer;
        functionBindings.insert(std::make_pair(id, func));
    }

    bool functionBindingExists(const std::string &id) const
    {
        if (functionBindings.find(id) == functionBindings.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    int getCurrentGlobalExpressionAddressOffset() const
    {
        return currentGlobalExpressionAddressOffset;
    }

    void incrementCurrentGlobalExpressionAddressOffset()
    {
        currentGlobalExpressionAddressOffset += 4;
    }

    void decrementCurrentGlobalExpressionAddressOffset()
    {
        currentGlobalExpressionAddressOffset -= 4;
    }

    void decrementCurrentGlobalExpressionAddressOffsetBy(const int &position)
    {
        currentGlobalExpressionAddressOffset -= position;
    }
};

//// VariableBindings ----------------------------------------------------

// stores bindings for the current scope and where they are in the stack
class LocalVariableBindings
{
    // holds the identifiers and the data of the local within the current scope
    std::unordered_map<std::string, Variable> localBindings; //localBindings;

    // the stackFrameSize is the value that must be added to the stack pointer
    // to pop the current stack frame out of the stack
    // also if subtracted from the frame pointer, we get the memory location
    // pointed by the stack pointer
    int stackFrameSize;

    // the currentExpressionAddressOffset is the value that must be subtracted from
    // the stack pointer to get the memory location of the current intermediate stored
    // expression
    int currentExpressionAddressOffset;

    //TODO:? Add switch label (list)
    // Loop Labels
    //std::string startLabel, endLabel;
    std::stack<std::string> startLabels;
    std::stack<std::string> endLabels;

public:
    LocalVariableBindings(int stackFrameSize_i = 0, int currentExpressionAddressOffset_i = 0) : stackFrameSize(stackFrameSize_i),
                                                                                                currentExpressionAddressOffset(currentExpressionAddressOffset_i){};

    void push_startLabel(std::string l)
    {
        startLabels.push(l);
    }

    void push_endLabel(std::string l)
    {
        endLabels.push(l);
    }

    void pop_startLabel()
    {
        startLabels.pop();
    }

    void pop_endLabel()
    {
        endLabels.pop();
    }

    std::string get_startLabel()
    {
        return startLabels.top();
    }

    std::string get_endLabel()
    {
        return endLabels.top();
    }

    int getStackFrameSize() const
    {
        return stackFrameSize;
    }

    int getCurrentExpressionAddressOffset() const
    {
        return currentExpressionAddressOffset;
    }

    PrimitiveDataTypeCode getLocalVariableDataTypeCode(const std::string &id) const
    {
        auto variableBinding = localBindings.find(id);
        return (*variableBinding).second.variableDataTypeCode;
    }

    const Array &getLocalArrayVariable(const std::string &id) const
    {
        auto variableBinding = localBindings.find(id);
        return (*variableBinding).second.arrayVariable;
    }

    int getLocalVariableAddressOffset(const std::string &id) const
    {
        auto variableBinding = localBindings.find(id);
        return (*variableBinding).second.addressOffset;
    }

    void insertLocalVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, bool isPointer)
    {
        Variable var;
        var.addressOffset = getStackFrameSize();
        var.is_array = false;
        var.variableDataTypeCode = dataTypeCode;
        var.is_pointer = isPointer;
        // if (dataTypeCode == DOUBLE)
        // {
        //     incrementStackFrameSize();
        // }
        incrementStackFrameSize();
        localBindings.insert(std::make_pair(id, var));
    }

    void insertLocalVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, int argRegNum, bool isPointer)
    {
        Variable var;
        var.addressOffset = argRegNum;
        var.is_array = false;
        var.variableDataTypeCode = dataTypeCode;
        var.is_pointer = isPointer;
        // if (dataTypeCode == DOUBLE)
        // {
        //     incrementStackFrameSize();
        // }
        localBindings.insert(std::make_pair(id, var));
    }

    bool localVariableBindingExists(const std::string &id) const
    {
        if (localBindings.find(id) == localBindings.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void insertLocalArrayVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, const std::vector<int> arrayDimensionSizes_i)
    {
        Variable var;
        var.addressOffset = getStackFrameSize() + 4;
        var.is_array = true;
        var.is_pointer = true;

        int arraySize = 1;
        for (int i = 0; i < arrayDimensionSizes_i.size(); i++)
        {
            arraySize *= arrayDimensionSizes_i[i];
        }
        arraySize *= 4;
        // if (dataTypeCode == _DOUBLE)
        // {
        //     arraySize *= 2;
        // }
        increaseStackFrameSizeBy(arraySize);

        Array varArray;
        varArray.setArrayDataTypeCode(dataTypeCode);
        varArray.setArrayDimensionalSizes(arrayDimensionSizes_i);
        var.arrayVariable = varArray;

        localBindings.insert(std::make_pair(id, var));
    }

    bool localVariableIsArray(const std::string &id)
    {
        auto variableBinding = localBindings.find(id);
        return (*variableBinding).second.is_array;
    }

    bool localVariableIsPointer(const std::string &id)
    {
        auto variableBinding = localBindings.find(id);
        return (*variableBinding).second.is_pointer;
    }

    void incrementStackFrameSize()
    {
        stackFrameSize += 4;
        currentExpressionAddressOffset += 4;
    }

    void increaseStackFrameSizeBy(const int &position)
    {
        stackFrameSize += position;
        currentExpressionAddressOffset += position;
    }

    void decrementStackFrameSize()
    {
        stackFrameSize -= 4;
        currentExpressionAddressOffset -= 4;
    }

    void decrementStackFrameSizeBy(const int &position)
    {
        stackFrameSize -= position;
        currentExpressionAddressOffset -= position;
    }

    void incrementCurrentExpressionAddressOffset()
    {
        currentExpressionAddressOffset += 4;
    }

    void decrementCurrentExpressionAddressOffset()
    {
        currentExpressionAddressOffset -= 4;
    }

    void decrementCurrentExpressionAddressOffsetBy(const int &position)
    {
        currentExpressionAddressOffset -= position;
    }

    // void addLoopLabeles() {
    //     startLabel =  Label::instance().uniquify("loop_start");
    //     endLabel = Label::instance().uniquify("loop_end");
    // }
};

#endif