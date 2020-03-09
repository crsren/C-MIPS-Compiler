#ifndef VARIABLE_BINDINGS_HPP
#define VARIABLE_BINDINGS_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class DataType;

// struct containing information on the variable declaration
struct VariableData
{
	DataType* type;
	int stack_position;
	std::vector<int> array_sizes;
};

// stores bindings for the current scope and where they are in the stack
class VariableBindings
{
private:
	static std::vector<std::string> string_literals;
	std::unordered_map<std::string, VariableData> bindings_;

public:
	VariableBindings();

	DataType* getType(const std::string &id) const;
};


#endif