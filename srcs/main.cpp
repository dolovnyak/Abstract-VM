#include <iostream>
#include <cassert>

#include "Operand.hpp"
#include "AbstractVmStack.hpp"
#include "CommandList.hpp"

void AddCommand(CommandList& commandList, std::list<std::string>& lexicalExceptionList, const std::string& command)
{
	try
	{
		commandList.AddCommand(command);
	}
	catch (const std::exception& exception)
	{
		lexicalExceptionList.emplace_back(exception.what());
	}
}

void RunCommands(CommandList& commandList, std::list<std::string>& lexicalExceptionsList)
{
	if (lexicalExceptionsList.empty())
	{
		try
		{
			commandList.Execute();
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
		}
	}
	else
	{
		for (const std::string& lexicalException : lexicalExceptionsList)
			std::cout << lexicalException << std::endl;
	}
}

void RunFromStandardOutput()
{
	CommandList commandList;
	std::list<std::string> lexicalExceptionList;
	
	while (true)
	{
		std::string command;
		std::getline(std::cin, command);
		
		if (command == ";;")
		{
			RunCommands(commandList, lexicalExceptionList);
			return;
		}
		
		AddCommand(commandList, lexicalExceptionList, command);
	}
}

int main(int argc, char **argv)
{
	std::string str = "asdasdasd1";
	
	size_t n = str.find_last_of('1');
	std::cout << (n == str.size() - 1) << std::endl;
	return 0;
	
	if (argc == 1)
	{
		RunFromStandardOutput();
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	try
	{
		AbstractVmStack vmStack;
		vmStack.Push(OperandType::Int8, "64");
		vmStack.Print();
		std::cout << std::endl;
		
		vmStack.Push(OperandType::Int16, "14525");
		vmStack.Push(OperandType::Int32, "145215");
		vmStack.Push(OperandType::Float, "14.5215");
		vmStack.Push(OperandType::Double, "14252.5215");
		vmStack.Dump();
		std::cout << std::endl;
		
		vmStack.Assert(OperandType::Double, "14252.5215");
		
		vmStack.Add();
		vmStack.Dump();
		
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
