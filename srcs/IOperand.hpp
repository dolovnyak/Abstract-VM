#pragma once

#include <iostream>

enum OperandType
{
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand
{
public:
	virtual int GetPrecision(void) const = 0; // Precision of the type of the instance
	virtual OperandType GetType(void) const = 0; // Type of the instance
	virtual const IOperand* operator+(const IOperand& rhs ) const = 0; // Sum
	virtual const IOperand* operator-(const IOperand& rhs ) const = 0; // Difference
	virtual const IOperand* operator*(const IOperand& rhs ) const = 0; // Product
	virtual const IOperand* operator/(const IOperand& rhs ) const = 0; // Quotient
	virtual const IOperand* operator%(const IOperand& rhs ) const = 0; // Mod
	virtual bool operator==(const IOperand& rhs ) const = 0; // Equal
	virtual bool operator!=(const IOperand& rhs ) const = 0; // Equal
	virtual const std::string& ToString(void) const = 0; // String representation of the instance
	virtual ~IOperand(void) {}
};