#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum PrimitiveDataTypeCode
{
    INTEGER,
    DOUBLE,
    FLOAT,
    CHAR,
    UNSIGNED
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
        for(int dimension = 0; dimension < arrayIndices.size(); dimension++)
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


// struct containing information on the variable declaration
struct Variable
{
	PrimitiveDataTypeCode variableDataTypeCode;

    Array arrayVariable;

	// the addressOffset is the value that must be subtracted from the stack pointer
	// to evaluate the memory location of the variable
	int addressOffset;

    bool is_array;
};

// stores bindings for the current scope and where they are in the stack
class VariableBindings
{
private:
	// note that this map holds the identifiers and the data of the local
	// variables defined within the current local scope
	std::unordered_map<std::string, Variable> localBindings;

	// note that this map holds the identifiers and the data of the global
	// variables
    //
    // ALSO note that in MIPS the variable identifiers correspond to the actual
    // memory address of the global variable
    // 
	// note that it is static since the global variables are shared by every
	// local scope and thus, by every instance of the VariableBindings class
	static std::unordered_map<std::string, Variable> globalBindings;

	// the stackFrameSize is the value that must be added to the stack pointer
	// to pop the current stack frame out of the stack
	// also if subtracted from the frame pointer, we get the memory location
	// pointed by the stack pointer
	int stackFrameSize;

    // the currentExpressionAddressOffset is the value that must be subtracted from
    // the stack pointer to get the memory location of the current intermediate stored
    // expression
    int currentExpressionAddressOffset;

public:
	VariableBindings(int stackFrameSize_i = 0, int currentExpressionAddressOffset_i = 4):
        stackFrameSize(stackFrameSize_i),
        currentExpressionAddressOffset(currentExpressionAddressOffset_i)
	    {}



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

    const Array& getLocalArrayVariable(const std::string &id) const
    {
        auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.arrayVariable;
    }

	int getLocalVariableAddressOffset(const std::string &id) const
	{
		auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.addressOffset;
	}



	void insertLocalVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode)
	{
        incrementStackFrameSize();
        Variable var;
        var.addressOffset = getStackFrameSize();
        var.is_array = false;
        var.variableDataTypeCode = dataTypeCode;
         if(dataTypeCode == DOUBLE)
        {
            incrementStackFrameSize();
        }
		localBindings.insert( std::make_pair(id, var) );
	}

	void insertLocalArrayVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, const std::vector<int> arrayDimensionSizes_i)
	{
        Variable var;
        var.addressOffset = getStackFrameSize() + 4;
        var.is_array = true;

        int arraySize = 1;
        for(int i = 0; i < arrayDimensionSizes_i.size(); i++)
        {
            arraySize *= arrayDimensionSizes_i[i];
        }
        arraySize *= 4;
        if(dataTypeCode == DOUBLE)
        {
            arraySize *= 2;
        }
        increaseStackFrameSizeBy(arraySize);

		Array varArray;
        varArray.setArrayDataTypeCode(dataTypeCode);
        varArray.setArrayDimensionalSizes(arrayDimensionSizes_i);
        var.arrayVariable = varArray;
        
		localBindings.insert( std::make_pair(id, var) );
	}



    void insertGlobalVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode)
	{
        Variable var;
        var.addressOffset = -1;
        var.is_array = false;
        var.variableDataTypeCode = dataTypeCode;
		globalBindings.insert( std::make_pair(id, var) );
	}

	void insertGlobalArrayVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, const std::vector<int> arrayDimensionSizes_i)
	{
        Variable var;
        var.addressOffset = -1;
        var.is_array = true;

        int arraySize = 1;
        for(int i = 0; i < arrayDimensionSizes_i.size(); i++)
        {
            arraySize *= arrayDimensionSizes_i[i];
        }
        arraySize *= 4;
        if(dataTypeCode == DOUBLE)
        {
            arraySize *= 2;
        }
        increaseStackFrameSizeBy(arraySize);

		Array varArray;
        varArray.setArrayDataTypeCode(dataTypeCode);
        varArray.setArrayDimensionalSizes(arrayDimensionSizes_i);
        var.arrayVariable = varArray;
        
		globalBindings.insert( std::make_pair(id, var) );
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
};

#endif