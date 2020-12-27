#include "AbstractVmStack.hpp"

void AbstractVmStack::Push(OperandType opType, const std::string& value)
{
	const IOperand* newOp = OperandFactory::CreateOperand(opType, value);
	_stack.push_front(newOp);
}

void AbstractVmStack::Pop()
{
	if (_stack.empty())
		throw PopOnEmptyStack();
	
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
		throw AssertOnEmptyStack(opType, value);
	
	if (*tmpOp != *_stack.front())
		throw AssertFailure(opType, value);
	
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
	if (_stack.empty())
		throw PrintOnEmptyStack();
	
	if (_stack.front()->GetType() != OperandType::Int8)
		throw PrintNotCorrectType(_stack.front()->GetType(), _stack.front()->ToString());
	
	std::cout << static_cast<char>(std::stoi(_stack.front()->ToString())) << std::endl;
}

void AbstractVmStack::Exit()
{
	while (!_stack.empty())
		this->Pop();
	
	exit(0);
}

void AbstractVmStack::Calculation(Operator opType)
{
	if (_stack.size() < 2)
		throw LowerThenTwoArgumentsCalculation(opType);
	
	const IOperand* tmpOp;
	switch (opType)
	{
		case Operator::Addition:
			tmpOp = *_stack[1] + *_stack[0];
			break;
		case Operator::Subtraction:
			tmpOp = *_stack[1] - *_stack[0];
			break;
		case Operator::Multiplication:
			tmpOp = *_stack[1] * *_stack[0];
			break;
		case Operator::Division:
			tmpOp = *_stack[1] / *_stack[0];
			break;
		case Operator::Mod:
			tmpOp = *_stack[1] % *_stack[0];
			break;
	}
	
	this->Pop();
	this->Pop();
	
	_stack.push_front(tmpOp);
}

AbstractVmStack::StackException::StackException(const std::string& strException)
: _strException("Stack exception: " + strException)
{
}

const char* AbstractVmStack::StackException::what() const throw()
{
	return _strException.c_str();
}

AbstractVmStack::PopOnEmptyStack::PopOnEmptyStack()
: StackException("try pop when stack is empty")
{
}


AbstractVmStack::AssertOnEmptyStack::AssertOnEmptyStack(OperandType operandType, const std::string& value)
: StackException("try assert when stack is empty " + to_string(operandType, value))
{
}

AbstractVmStack::AssertFailure::AssertFailure(OperandType operandType, const std::string& value)
: StackException("assert failure " + to_string(operandType, value))
{
}

AbstractVmStack::LowerThenTwoArgumentsCalculation::LowerThenTwoArgumentsCalculation(Operator operatorType)
: StackException("try " + to_string(operatorType) + "when stack has lower than two values")
{
}

AbstractVmStack::PrintOnEmptyStack::PrintOnEmptyStack()
: StackException("try print when stack is empty")
{
}

AbstractVmStack::PrintNotCorrectType::PrintNotCorrectType(OperandType operandType, const std::string& value)
: StackException("try print incorrect value" + to_string(operandType, value))
{
}
