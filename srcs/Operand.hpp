#pragma once

#include "IOperand.hpp"
#include "OperandFactory.hpp"


template<typename T>
class Operand : public IOperand
{
public:
	Operand<T>(OperandType type, T value);
	Operand<T>(const Operand<T>& op);
	Operand<T>& operator=(const Operand<T>& op);
	virtual ~Operand<T>() {}
	
	const IOperand* Calculation(Operator operatorType, const IOperand& rightOperand) const;
	
	const IOperand* operator+(const IOperand& rightOperand) const override;
	const IOperand* operator-(const IOperand& rightOperand) const override;
	const IOperand* operator*(const IOperand& rightOperand) const override;
	const IOperand* operator/(const IOperand& rightOperand) const override;
	const IOperand* operator%(const IOperand& rightOperand) const override;
	bool operator==(const IOperand& rightOperand) const override;
	bool operator!=(const IOperand& rightOperand) const override;
	
	const T& GetValue(void) const { return _value; }
	
	int GetPrecision(void) const override { return (int)GetType(); }
	OperandType GetType(void) const override { return _type; }
	const std::string& ToString(void) const override { return _strValue; }
	const std::string& ToStringWithPrecision(void) const override { return _strValueWithFullPrecision; }

private:
	T _value;
	std::string _strValue;
	std::string _strValueWithFullPrecision;
	OperandType _type;
	
	Operand<T>() {}
	static bool IsFractional(OperandType type);
	static long double GetFractionalValue(const IOperand& op);
	static int64_t GetIntegerValue(const IOperand& op);
};


template<typename T>
Operand<T>::Operand(OperandType type, T value) : _type(type), _value(value)
{
	if (!IsFractional(type))
	{
		_strValue = std::to_string(value);
		_strValueWithFullPrecision = _strValue;
	}
	else
	{
		_strValue = to_string_precision(value, 2);
		_strValueWithFullPrecision = to_string_precision(value);
	}
}

template<typename T>
Operand<T>::Operand(const Operand<T>& op)
{
	*this = op;
}

template<typename T>
const IOperand* Operand<T>::Calculation(Operator operatorType, const IOperand& rightOperand) const
{
	{
		OperandType maxType = this->GetPrecision() > rightOperand.GetPrecision() ? this->GetType() : rightOperand.GetType();
		
		if (!IsFractional(maxType))
		{
			int64_t secondOpValue = static_cast<int64_t>(GetIntegerValue(rightOperand));
			
			switch (operatorType)
			{
				case Operator::Addition:
					return OperandFactory::CreateOperand
					(maxType, std::to_string(static_cast<int64_t>(_value) + secondOpValue));
				case Operator::Subtraction:
					return OperandFactory::CreateOperand
					(maxType, std::to_string(static_cast<int64_t>(_value) - secondOpValue));
				case Operator::Multiplication:
					return OperandFactory::CreateOperand
					(maxType, std::to_string(static_cast<int64_t>(_value) * secondOpValue));
				case Operator::Division:
					if (secondOpValue == 0)
						throw std::logic_error("division by 0");
					return OperandFactory::CreateOperand
					(maxType, std::to_string(static_cast<int64_t>(_value) / secondOpValue));
				case Operator::Mod:
					if (secondOpValue == 0)
						throw std::logic_error("mod by 0");
					return OperandFactory::CreateOperand
					(maxType, std::to_string(static_cast<int64_t>(_value) % secondOpValue));
			}
		}
		else
		{
			long double secondOpValue = IsFractional(rightOperand.GetType()) ?
					static_cast<long double>(GetFractionalValue(rightOperand)) :
					static_cast<long double>(GetIntegerValue(rightOperand));
					
			switch (operatorType)
			{
				case Operator::Addition:
					return OperandFactory::CreateOperand
					(maxType, to_string_precision(static_cast<long double>(_value) + secondOpValue));
				case Operator::Subtraction:
					return OperandFactory::CreateOperand
					(maxType, to_string_precision(static_cast<long double>(_value) - secondOpValue));
				case Operator::Multiplication:
					return OperandFactory::CreateOperand
					(maxType, to_string_precision(static_cast<long double>(_value) * secondOpValue));
				case Operator::Division:
					if (secondOpValue == 0)
						throw std::logic_error("division by 0");
					return OperandFactory::CreateOperand
					(maxType, to_string_precision(static_cast<long double>(_value) / secondOpValue));
				case Operator::Mod:
					throw std::logic_error("mod doesn't correct with fractional values");
			}
		}
		throw std::logic_error("operator type doesn't correct");
	}
}

template<typename T>
int64_t Operand<T>::GetIntegerValue(const IOperand& op)
{
	if (op.GetType() == OperandType::Int8)
		return static_cast<int64_t>(dynamic_cast<const Operand<int8_t>*>(&op)->GetValue());
	else if (op.GetType() == OperandType::Int16)
		return static_cast<int64_t>(dynamic_cast<const Operand<int16_t>*>(&op)->GetValue());
	
	return static_cast<int64_t>(dynamic_cast<const Operand<int32_t>*>(&op)->GetValue());
}

template<typename T>
long double Operand<T>::GetFractionalValue(const IOperand& op)
{
	if (op.GetType() == OperandType::Float)
		return static_cast<long double>(dynamic_cast<const Operand<float>*>(&op)->GetValue());
	
	return static_cast<long double>(dynamic_cast<const Operand<double>*>(&op)->GetValue());
}

template<typename T>
bool Operand<T>::IsFractional(OperandType type)
{
	if (type == OperandType::Float || type == OperandType::Double)
		return true;
	return false;
}

template<typename T>
Operand<T>& Operand<T>::operator=(const Operand<T>& op)
{
	if (this == &op)
		return *this;
	
	_value = op._value;
	_strValue = op._strValue;
	_type = op._type;
	
	return *this;
}

template<typename T>
bool Operand<T>::operator==(const IOperand& rightOperand) const
{
	if (_type != rightOperand.GetType())
		return false;
	
	if (_value != dynamic_cast<const Operand<T>*>(&rightOperand)->GetValue())
		return false;
	
	return true;
}

template<typename T>
bool Operand<T>::operator!=(const IOperand& rightOperand) const
{
	return !(*this == rightOperand);
}

template<typename T>
const IOperand* Operand<T>::operator+(const IOperand& rightOperand) const
{
	return Calculation(Operator::Addition, rightOperand);
}

template<typename T>
const IOperand* Operand<T>::operator-(const IOperand& rightOperand) const
{
	return Calculation(Operator::Subtraction, rightOperand);
}

template<typename T>
const IOperand* Operand<T>::operator*(const IOperand& rightOperand) const
{
	return Calculation(Operator::Multiplication, rightOperand);
}

template<typename T>
const IOperand* Operand<T>::operator/(const IOperand& rightOperand) const
{
	return Calculation(Operator::Division, rightOperand);
}

template<typename T>
const IOperand* Operand<T>::operator%(const IOperand& rightOperand) const
{
	return Calculation(Operator::Mod, rightOperand);
}
