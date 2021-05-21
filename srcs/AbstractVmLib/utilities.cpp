#include "utilities.hpp"

bool contains(const std::string& orig, const std::string& income)
{
	std::size_t found = orig.find(income);
	
	if (found != std::string::npos)
		return true;
	return false;
}

bool isFractional(OperandType type)
{
	if (type == OperandType::Float || type == OperandType::Double)
		return true;
	return false;
}

std::string to_string(Operator op)
{
	switch (op)
	{
		case Operator::Addition:		return "add";
		case Operator::Subtraction:		return "sub";
		case Operator::Multiplication:	return "mul";
		case Operator::Division:		return "div";
		case Operator::Mod:				return "mod";
	}
}

std::string to_string(OperandType type)
{
	switch (type)
	{
		case OperandType::Int8:			return "int8";
		case OperandType::Int16:		return "int16";
		case OperandType::Int32:		return "int32";
		case OperandType::Float:		return "float";
		case OperandType::Double:		return "double";
		case OperandType::Incorrect:	return "incorrect";
	}
}

std::string to_string(OperandType type, const std::string& value)
{
	return "(type - " + to_string(type) + ", value - " + value + ")";
}

std::string to_string(const IOperand& op)
{
	return "(type - " + to_string(op.GetType()) + ", value - " + op.ToString() + ")";
}

int8_t stoi8(const std::string& value)
{
	int tmpValue = std::stoi(value);
	
	if (tmpValue < -128 || tmpValue > 127)
		throw std::out_of_range("");
	
	return static_cast<int8_t>(tmpValue);
}

int16_t	stoi16(const std::string& value)
{
	int tmpValue = std::stoi(value);
	
	if (tmpValue < -32768 || tmpValue > 32767)
		throw std::out_of_range("");
	
	return static_cast<int16_t>(tmpValue);
}
