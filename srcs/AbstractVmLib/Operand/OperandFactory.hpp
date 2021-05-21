#pragma once

#include "IOperand.hpp"
#include "utilities.hpp"

class OperandFactory
{
public:
	static const IOperand* CreateOperand(OperandType type, const std::string& value);
	
private:
	static const IOperand* CreateInt8(const std::string& value);
	static const IOperand* CreateInt16(const std::string& value);
	static const IOperand* CreateInt32(const std::string& value);
	static const IOperand* CreateFloat(const std::string& value);
	static const IOperand* CreateDouble(const std::string& value);
};
