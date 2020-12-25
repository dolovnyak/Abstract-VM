#include "CommandList.hpp"

void CommandList::AddCommand(std::string command)
{
	std::vector<std::string> commandWords;
	
	split(command, commandWords, ' ');
	
	if (commandWords.size() > 2)
		throw std::logic_error("The assembly program includes one or several lexical errors or syntactic errors");
	
	if (commandWords.size() == 1)
	{
		AddCommandWithoutValue(commandWords.back());
	}
	else
	{
		AddCommandWithValue(commandWords);
	}
}

void CommandList::Execute()
{

}

void CommandList::AddCommandWithoutValue(const std::string& strCommand)
{
	Command command;
	
	if (strCommand == "pop")
		command.commandType = CommandType::Pop;
	else if (strCommand == "dump")
		command.commandType = CommandType::Dump;
	else if (strCommand == "add")
		command.commandType = CommandType::Add;
	else if (strCommand == "sub")
		command.commandType = CommandType::Sub;
	else if (strCommand == "mul")
		command.commandType = CommandType::Mul;
	else if (strCommand == "div")
		command.commandType = CommandType::Div;
	else if (strCommand == "mod")
		command.commandType = CommandType::Modulo;
	else if (strCommand == "print")
		command.commandType = CommandType::Print;
	else if (strCommand == "exit")
		command.commandType = CommandType::Exit;
	else
		throw std::logic_error("command type is incorrect"); //TODO more fully error
	
	_commandList.push_back(command);
}

void CommandList::AddCommandWithValue(const std::vector<std::string>& commandWords)
{
	Command command;
	
	if (commandWords[0] == "push")
		command.commandType = CommandType::Push;
	else if (commandWords[0] == "assert")
		command.commandType = CommandType::Assert;
	else
		throw std::logic_error("command type is incorrect"); //TODO more fully error
	
	std::vector<std::string> typeAndValue;
	split(commandWords[1], typeAndValue, '(');
	
	command.operandType = GetOperandType(typeAndValue[0]);
	command.value = GetOperandValue(typeAndValue[1]);
}

OperandType CommandList::GetOperandType(const std::string& strOperandType)
{
	if (strOperandType == "int8")
		return OperandType::Int8;
	else if (strOperandType == "int16")
		return OperandType::Int16;
	else if (strOperandType == "int32")
		return OperandType::Int32;
	else if (strOperandType == "float")
		return OperandType::Float;
	else if (strOperandType == "double")
		return OperandType::Double;
	
	throw std::logic_error("value type is incorrect"); //TODO more fully error
}

std::string CommandList::GetOperandValue(const std::string& operandValue)
{
	//TODO
	return std::string();
}

