#include "CommandList.hpp"

void CommandList::AddCommand(const std::string& command)
{
	std::vector<std::string> commandWords;
	
	split(command, commandWords, ' ');
	
	if (commandWords.empty() || commandWords.size() > 2)
		throw std::logic_error("not correct number of words in command");
	
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
	if (_commandList.back().commandType != CommandType::Exit)
		throw std::logic_error("The program doesn't have an exit instruction or there are instructions after exit");
	
	AbstractVmStack abstractVmStack;
	
	for (const Command& command: _commandList)
	{
		switch (command.commandType)
		{
			case CommandType::Push:
				abstractVmStack.Push(command.operandType, command.value);
				break;
			case Pop:
				abstractVmStack.Pop();
				break;
			case Dump:
				abstractVmStack.Dump();
				break;
			case Assert:
				abstractVmStack.Assert(command.operandType, command.value);
				break;
			case Add:
				abstractVmStack.Add();
				break;
			case Sub:
				abstractVmStack.Sub();
				break;
			case Mul:
				abstractVmStack.Mul();
				break;
			case Div:
				abstractVmStack.Div();
				break;
			case Modulo:
				abstractVmStack.Mod();
				break;
			case Print:
				abstractVmStack.Print();
				break;
			case Exit:
				abstractVmStack.Exit();
				break;
		}
	}
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
		
	command.operandType = OperandType::Incorrect;
	command.value = "";
	
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
	
	if (typeAndValue.size() != 2 || typeAndValue[1].find_last_of(')') != typeAndValue[1].size() - 1)
		throw std::logic_error("incorrect parentheses"); //TODO more fully error
	
	typeAndValue[1].erase(typeAndValue[1].size() - 1);
	
	command.operandType = GetOperandType(typeAndValue[0]);
	command.value = GetOperandValue(typeAndValue[1], command.operandType);
	
	_commandList.push_back(command);
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

std::string CommandList::GetOperandValue(const std::string& operandValue, OperandType operandType)
{
	bool containsDot = false;
	int i = 0;
	
	if (operandValue[0] == '-' && operandValue.size() > 1)
		i++;
	else if (operandValue[0] == '-')
		throw std::logic_error("value is incorrect"); //TODO more fully error
	
	for (; i < operandValue.size(); i++)
	{
		if (!isdigit(operandValue[i]))
		{
			if (operandValue[i] == '.' && isFractional(operandType))
			{
				if (containsDot)
					throw std::logic_error("few dots in number");
				containsDot = true;
			}
			else
				throw std::logic_error("value is incorrect"); //TODO more fully error
		}
	}
	
	return operandValue;
}

//push int32(42)
//push int32(33)
//add
//push float(44.55)
//mul
//push double(42.42)
//push int32(42)
//dump
//pop
//assert double(42.42)
//exit
//;;