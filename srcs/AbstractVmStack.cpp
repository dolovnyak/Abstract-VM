#include "AbstractVmStack.hpp"

void AbstractVmStack::Push(OperandType opType, const std::string& value)
{
	const IOperand* newOp = OperandFactory::CreateOperand(opType, value);
	_stack.push_front(newOp);
}

void AbstractVmStack::Pop()
{
	//TODO add exception if stack is empty
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
	
	if (*tmpOp != *_stack.front())
		throw std::logic_error("Assert types aren't equal");
	
	delete tmpOp;
}

void AbstractVmStack::Add()
{

}

void AbstractVmStack::Sub()
{

}

void AbstractVmStack::Mul()
{

}

void AbstractVmStack::Div()
{

}

void AbstractVmStack::Mod()
{

}

void AbstractVmStack::Print()
{

}

void AbstractVmStack::Exit()
{

}
