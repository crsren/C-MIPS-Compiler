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
	// note that it is static since the global variables are shared by every
	// local scope and thus, by every instance of the VariableBindings class
	static std::unordered_map<std::string, Variable> globalBindings;

	// the stackFrameSize is the value that must be added to the stack pointer
	// to pop the current stack frame out of the stack
	// also if subtracted from the frame pointer, we get the memory location
	// pointed by the stack pointer
	int stackFrameSize;

public:
	VariableBindings(int stackFrameSize_i = 0): stackFrameSize(stackFrameSize_i)
	{}



	int getStackFrameSize() const
	{
		return stackFrameSize;
	}

	PrimitiveDataTypeCode getVariableDataTypeCode(const std::string &id) const
    {
        auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.variableDataTypeCode;
    }

    const Array& getArrayVariable(const std::string &id) const
    {
        auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.arrayVariable;
    }

	int getVariableAddressOffset(const std::string &id) const
	{
		auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.addressOffset;
	}



	void insertVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode)
	{
        incrementStackFrameSize();
        Variable var;
        var.addressOffset = getStackFrameSize();
        var.is_array = false;
        var.variableDataTypeCode = dataTypeCode;
		localBindings.insert( std::make_pair(id, var) );
	}

	void insertArrayVariableBinding(const std::string &id, const PrimitiveDataTypeCode &dataTypeCode, const std::vector<int> arrayDimensionSizes_i)
	{
        Variable var;
        var.addressOffset = getStackFrameSize() + 4;
        var.is_array = true;

        int arraySize = 1;
        for(int i = 0; i < arrayDimensionSizes_i.size(); i++)
        {
            arraySize *= arrayDimensionSizes_i[i];
        }
        increaseStackFrameSizeBy(arraySize);

		Array varArray;
        varArray.setArrayDataTypeCode(dataTypeCode);
        varArray.setArrayDimensionalSizes(arrayDimensionSizes_i);
        var.arrayVariable = varArray;
        
		localBindings.insert( std::make_pair(id, var) );
	}
	


	void incrementStackFrameSize()
	{
		stackFrameSize += 4;
	}

	void increaseStackFrameSizeBy(const int &position)
	{
		stackFrameSize += position;
	}

	void decrementStackFrameSize()
	{
		stackFrameSize -= 4;
	}

	void decrementStackFrameSizeBy(const int &position)
	{
		stackFrameSize -= position;
	}
};

#endif