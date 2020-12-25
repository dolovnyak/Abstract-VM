#include "OperandFactory.hpp"
#include "Operand.hpp"

const IOperand* OperandFactory::CreateOperand(OperandType type, const std::string& value)
{
	switch (type)
	{
		case OperandType::Int8:
			return CreateInt8(value);
		case OperandType::Int16:
			return CreateInt16(value);
		case OperandType::Int32:
			return CreateInt32(value);
		case OperandType::Float:
			return CreateFloat(value);
		case OperandType::Double:
			return CreateDouble(value);
		case Incorrect:
			throw std::logic_error("Operand type is incorrect");
	}
}

//stoi, stof, stod have "out of range" exception
const IOperand* OperandFactory::CreateInt8(const std::string& value)
{
	int tmpValue = std::stoi(value);
	
	if (tmpValue < -128 || tmpValue > 127)
		throw std::logic_error("out of range");
	
	return new Operand<int8_t>(OperandType::Int8, (int8_t)tmpValue);
}

const IOperand* OperandFactory::CreateInt16(const std::string& value)
{
	int tmpValue = std::stoi(value);
	
	if (tmpValue < -32768 || tmpValue > 32767)
		throw std::logic_error("out of range");
	
	return new Operand<int16_t>(OperandType::Int16, (int16_t)tmpValue);
}

const IOperand* OperandFactory::CreateInt32(const std::string& value)
{
	int tmpValue = std::stoi(value);
	return new Operand<int>(OperandType::Int32, tmpValue);
}

const IOperand* OperandFactory::CreateFloat(const std::string& value)
{
	float tmpValue = std::stof(value);
	return new Operand<float>(OperandType::Float, tmpValue);
}

const IOperand* OperandFactory::CreateDouble(const std::string& value)
{
	double tmpValue = std::stod(value);
	return new Operand<double>(OperandType::Double, tmpValue);
}
