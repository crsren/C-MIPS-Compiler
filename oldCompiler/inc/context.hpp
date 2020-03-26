#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class DataType;

// struct containing information on the variable declaration
struct VariableData
{
	DataType* type;

	// the stackFramePosition is the value that must be added to the stack pointer
	// to evaluate the memory location of the variable
	// IF THE STACK FRAME POSITION IS NEGATIVE (it can take the values [-1, -8]),
	// then taking the |stackFramePosition + 1| will indicate the index of the
	// "Saved Register" (i.e. $s0, $s1, ... , $s7) in which the variable is stored
	int stackFramePosition;

	// the size of the vector is the dimensions of the multi-dimensional array
	// the elements of the vector are the respective sizes of each dimension
	std::vector<int> arrayDimensionSizes;
};

// stores bindings for the current scope and where they are in the stack
class VariableBindings
{
private:
	// note that this map holds the identifiers and the data of the local
	// variables defined within the current local scope
	std::unordered_map<std::string, VariableData> localBindings;

	// note that this map holds the identifiers and the data of the global
	// variables
	// note that it is static since the global variables are shared by every
	// local scope and thus, by every instance of the VariableBindings class
	static std::unordered_map<std::string, VariableData> globalBindings;

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

	DataType* getVariableDataType(const std::string &id) const
	{
		auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.type;
	}

	int getVariableStackFramePosition(const std::string &id) const
	{
		auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.stackFramePosition;
	}

	const std::vector<int> &getVariableArrayDimensionSizes(const std::string &id) const
	{
		auto variableBinding = localBindings.find(id);
		return (*variableBinding).second.arrayDimensionSizes;
	}



	void insertVariableBinding(const std::string &id, const DataType* &type_i, const int &stackFramePosition_i)
	{
		VariableData varData;
		varData.type = type_i;
		varData.stackFramePosition = stackFramePosition_i;
		localBindings.insert( std::make_pair(id, varData) );
	}

	void insertArrayVariableBinding(const std::string &id, const DataType* &type_i, const int &stackFramePosition_i, const std::vector<int> arrayDimensionSizes_i)
	{
		VariableData varData;
		varData.type = type_i;
		varData.stackFramePosition = stackFramePosition_i;
		varData.arrayDimensionSizes = arrayDimensionSizes_i;
		localBindings.insert( std::make_pair(id, varData) );
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