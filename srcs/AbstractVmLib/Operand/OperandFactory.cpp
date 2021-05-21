#include "OperandFactory.hpp"
#include "Operand.hpp"

void throwCorrectException(OperandType type, const std::string& value)
{
	if (value[0] == '-')
		throw Underflow(type, value);
	else
		throw Overflow(type, value);
}

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
			throw IncorrectType(type, value);
	}
}

//stoi, stof, stod have "out of range" exception
const IOperand* OperandFactory::CreateInt8(const std::string& value)
{
	try
	{
		int8_t tmpValue = stoi8(value);
		return new Operand<int8_t>(OperandType::Int8, (int8_t)tmpValue);
	}
	catch (const std::exception& e)
	{
		throwCorrectException(OperandType::Int8, value);
	}
	
	throw Impossible(OperandType::Int8, value);
}

const IOperand* OperandFactory::CreateInt16(const std::string& value)
{
	try
	{
		int16_t tmpValue = stoi16(value);
		return new Operand<int16_t>(OperandType::Int16, (int16_t) tmpValue);
	}
	catch (const std::exception& e)
	{
		throwCorrectException(OperandType::Int16, value);
	}
	
	throw Impossible(OperandType::Int16, value);
}

const IOperand* OperandFactory::CreateInt32(const std::string& value)
{
	try
	{
		int tmpValue = std::stoi(value);
		return new Operand<int>(OperandType::Int32, tmpValue);
	}
	catch (const std::exception& e)
	{
		throwCorrectException(OperandType::Int32, value);
	}
	
	throw Impossible(OperandType::Int32, value);
}

const IOperand* OperandFactory::CreateFloat(const std::string& value)
{
	try
	{
		float tmpValue = std::stof(value);
		return new Operand<float>(OperandType::Float, tmpValue);
	}
	catch (const std::exception& e)
	{
		throwCorrectException(OperandType::Float, value);
	}
	
	throw Impossible(OperandType::Float, value);
}

const IOperand* OperandFactory::CreateDouble(const std::string& value)
{
	try
	{
		double tmpValue = std::stod(value);
		return new Operand<double>(OperandType::Double, tmpValue);
	}
	catch (const std::exception& e)
	{
		throwCorrectException(OperandType::Double, value);
	}
	
	throw Impossible(OperandType::Double, value);
}
