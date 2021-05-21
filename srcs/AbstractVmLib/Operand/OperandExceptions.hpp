#pragma once

#include "IOperand.hpp"
#include "utilities.hpp"

class OperandException : public std::exception
{
public:
	OperandException(const std::string& strException);
	const char* what() const throw() override;

private:
	const std::string _strException;
};

class DivisionByZero : public OperandException
{
public:
	DivisionByZero(const IOperand& left, const IOperand& right);
};

class ModuloByZero : public OperandException
{
public:
	ModuloByZero(const IOperand& left, const IOperand& right);
};

class ModuloWithFractionalValues : public OperandException
{
public:
	ModuloWithFractionalValues(const IOperand& left, const IOperand& right);
};

class Overflow : public OperandException
{
public:
	Overflow(OperandType type, const std::string& value);
};

class Underflow : public OperandException
{
public:
	Underflow(OperandType type, const std::string& value);
};

class IncorrectType : public OperandException
{
public:
	IncorrectType(OperandType type, const std::string& value);
};

class Impossible : public OperandException
{
public:
	Impossible(OperandType type, const std::string& value);
};
