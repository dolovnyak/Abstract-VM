#include "AbstractVmStack.hpp"

void AbstractVmStack::Push(OperandType opType, const std::string& value)
{
	const IOperand* newOp = OperandFactory::CreateOperand(opType, value);
	_stack.push_front(newOp);
}

void AbstractVmStack::Pop()
{
	if (_stack.empty())
		throw std::logic_error("pop when stack is empty");
	
	delete _stack.front();
	_stack.pop_front();
}

void AbstractVmStack::Dump()
{
	for (const IOperand* op : _stack)
	{
		std::cout << op->ToString() << std::endl;
	}
}

void AbstractVmStack::Assert(OperandType opType, const std::string& value)
{
	const IOperand* tmpOp = OperandFactory::CreateOperand(opType, value);
	
	if (_stack.empty())
		throw std::logic_error("assert instruction when stack is empty");
	
	if (*tmpOp != *_stack.front())
		throw std::logic_error("assert instruction is not true");
	
	delete tmpOp;
}

void AbstractVmStack::Add()
{
	Calculation(Operator::Addition);
}

void AbstractVmStack::Sub()
{
	Calculation(Operator::Subtraction);
}

void AbstractVmStack::Mul()
{
	Calculation(Operator::Multiplication);
}

void AbstractVmStack::Div()
{
	Calculation(Operator::Division);
}

void AbstractVmStack::Mod()
{
	Calculation(Operator::Mod);
}

void AbstractVmStack::Print()
{
	if (_stack.front()->GetType() != OperandType::Int8)
		throw std::logic_error("try to print non 8-bit integer");
	
	std::cout << static_cast<char>(std::stoi(_stack.front()->ToString())) << std::endl;
}

void AbstractVmStack::Exit()
{
	while (!_stack.empty())
		this->Pop();
	
	//TODO
	exit(0);
}

void AbstractVmStack::Calculation(Operator opType)
{
	if (_stack.size() <= 2)
		throw std::logic_error("stack is composed of strictly less that two values when an arithmetic instruction is executed");
	
	const IOperand* tmpOp;
	switch (opType)
	{
		case Operator::Addition:
			tmpOp = *_stack[0] + *_stack[1];
			break;
		case Operator::Subtraction:
			tmpOp = *_stack[0] - *_stack[1];
			break;
		case Operator::Multiplication:
			tmpOp = *_stack[0] * *_stack[1];
			break;
		case Operator::Division:
			tmpOp = *_stack[0] / *_stack[1];
			break;
		case Operator::Mod:
			tmpOp = *_stack[0] % *_stack[1];
			break;
	}
	
	this->Pop();
	this->Pop();
	
	_stack.push_front(tmpOp);
}