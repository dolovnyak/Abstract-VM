#include "OperandExceptions.hpp"

OperandException::OperandException(const std::string& strException)
: _strException("Operand exception: " + strException)
{
}

const char* OperandException::what() const throw()
{
	return _strException.c_str();
}

DivisionByZero::DivisionByZero(const IOperand& left, const IOperand& right)
: OperandException("division by zero " + to_string(left) + "/" + to_string(right))
{
}

ModuloByZero::ModuloByZero(const IOperand& left, const IOperand& right)
: OperandException("modulo by zero " + to_string(left) + "/" + to_string(right))
{
}

ModuloWithFractionalValues::ModuloWithFractionalValues(const IOperand& left, const IOperand& right)
: OperandException("modulo with fractional values " + to_string(left) + "%" + to_string(right))
{
}

Overflow::Overflow(OperandType type, const std::string& value)
: OperandException("operand overflow " + to_string(type, value))
{
}

Underflow::Underflow(OperandType type, const std::string& value)
: OperandException("operand underflow " + to_string(type, value))
{
}

Impossible::Impossible(OperandType type, const std::string& value)
: OperandException("impossible exception " + to_string(type, value))
{
}

IncorrectType::IncorrectType(OperandType type, const std::string& value)
: OperandException("Incorrect type " + to_string(type, value))
{
}
