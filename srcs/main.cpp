#include <iostream>
#include <cassert>

#include "Operand.hpp"
#include "AbstractVmStack.hpp"

int main()
{
	try
	{
		AbstractVmStack vmStack;
		vmStack.Push(OperandType::Int8, "14");
		vmStack.Push(OperandType::Int16, "14525");
		vmStack.Push(OperandType::Int32, "145215");
		vmStack.Push(OperandType::Float, "14.5215");
		vmStack.Push(OperandType::Double, "14252.5215");
		vmStack.Dump();
		
		vmStack.Assert(OperandType::Double, "14252.5215");
		
		std::cout << std::endl;
		vmStack.Pop();
		vmStack.Dump();
		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
