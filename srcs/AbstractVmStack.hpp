#pragma once

#include "OperandFactory.hpp"
#include <deque>

class AbstractVmStack
{
public:
	AbstractVmStack();
	AbstractVmStack(const AbstractVmStack& abstractVmStack);
	AbstractVmStack& operator=(const AbstractVmStack& abstractVmStack);
	~AbstractVmStack();
	
	void Push(OperandType opType, const std::string& value);
	void Pop();
	void Dump();
	void Assert(OperandType opType, const std::string& value);
	void Add();
	void Sub();
	void Mul();
	void Div();
	void Mod();
	void Print();
	void Exit();
	

private:
	std::deque<const IOperand*> _stack;
	
	void Calculation(Operator opType);
	
	class StackException : public std::exception
	{
	public:
		StackException(const std::string& strException);
		const char* what() const throw() override;
	
	private:
		const std::string _strException;
	};
	
	
	class PopOnEmptyStack : public StackException
	{
	public:
		PopOnEmptyStack();
	};
	
	class AssertOnEmptyStack : public StackException
	{
	public:
		AssertOnEmptyStack(OperandType operandType, const std::string& value);
	};
	
	class AssertFailure : public StackException
	{
	public:
		AssertFailure(OperandType operandType, const std::string& value);
	};
	
	class LowerThenTwoArgumentsCalculation : public StackException
	{
	public:
		LowerThenTwoArgumentsCalculation(Operator operatorType);
	};
	
	class PrintOnEmptyStack : public StackException
	{
	public:
		PrintOnEmptyStack();
	};
	
	class PrintNotCorrectType : public StackException
	{
	public:
		PrintNotCorrectType(OperandType operandType, const std::string& value);
	};
};
