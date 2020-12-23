#pragma once

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <deque>

class AbstractVmStack
{
public:
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
};
