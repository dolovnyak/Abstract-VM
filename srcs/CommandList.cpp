#include "CommandList.hpp"

CommandList::CommandList()
{
}

CommandList::CommandList(const CommandList& commandList)
{
	*this = commandList;
}

CommandList& CommandList::operator=(const CommandList& commandList)
{
	if (this == &commandList)
		return *this;
	
	_commandList = commandList._commandList;
	
	return *this;
}

CommandList::~CommandList()
{
}

void CommandList::AddCommand(const std::string& command)
{
	Lexer lexer;
	lexer.ParseIntoLexemes(command);
	
	Parser parser(lexer.GetLexemes(), command);
	parser.ParseLexemes();
	
	if (parser.GetInstructionType() == InstructionType::CommandWithoutValue)
	{
		AddCommandWithoutValue(parser.GetCommandType(), command);
	}
	else
	{
		AddCommandWithValue(parser.GetCommandType(), parser.GetValueType(), parser.GetValue(), command);
	}
}

void CommandList::Execute()
{
	if (_commandList.empty() || _commandList.back().commandType != CommandType::Exit)
		throw NotCorrectExit();
	
	AbstractVmStack abstractVmStack;
	
	for (const Command& command: _commandList)
	{
		switch (command.commandType)
		{
			case CommandType::Push:
				abstractVmStack.Push(command.valueType, command.value);
				break;
			case Pop:
				abstractVmStack.Pop();
				break;
			case Dump:
				abstractVmStack.Dump();
				break;
			case Assert:
				abstractVmStack.Assert(command.valueType, command.value);
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

void CommandList::AddCommandWithoutValue(const std::string& commandType, const std::string& rawCommand)
{
	Command command;
	
	if (commandType == "pop")
		command.commandType = CommandType::Pop;
	else if (commandType == "dump")
		command.commandType = CommandType::Dump;
	else if (commandType == "add")
		command.commandType = CommandType::Add;
	else if (commandType == "sub")
		command.commandType = CommandType::Sub;
	else if (commandType == "mul")
		command.commandType = CommandType::Mul;
	else if (commandType == "div")
		command.commandType = CommandType::Div;
	else if (commandType == "mod")
		command.commandType = CommandType::Modulo;
	else if (commandType == "print")
		command.commandType = CommandType::Print;
	else if (commandType == "exit")
		command.commandType = CommandType::Exit;
	else
		throw IncorrectCommandType(commandType, rawCommand);
		
	command.valueType = OperandType::Incorrect;
	command.value = "";
	
	_commandList.push_back(command);
}

void CommandList::AddCommandWithValue(const std::string& commandType, const std::string& valueType,
						 const std::string& value, const std::string& rawCommand)
{
	Command command;
	
	if (commandType == "push")
		command.commandType = CommandType::Push;
	else if (commandType == "assert")
		command.commandType = CommandType::Assert;
	else
		throw IncorrectCommandType(commandType, rawCommand);
	
	command.valueType = GetValueType(valueType, rawCommand);
	command.value = GetValue(value, command.valueType, rawCommand);
	
	_commandList.push_back(command);
}

OperandType CommandList::GetValueType(const std::string& strValueType, const std::string& rawCommand)
{
	if (strValueType == "int8")
		return OperandType::Int8;
	else if (strValueType == "int16")
		return OperandType::Int16;
	else if (strValueType == "int32")
		return OperandType::Int32;
	else if (strValueType == "float")
		return OperandType::Float;
	else if (strValueType == "double")
		return OperandType::Double;
	
	throw IncorrectValueType(strValueType, rawCommand);
}

std::string CommandList::GetValue(const std::string& value, OperandType type, const std::string& rawCommand)
{
	bool containsDot = false;
	int i = 0;
	
	if (value == "-." || value == ".")
		throw IncorrectValue(value, rawCommand);
	
	if (value[0] == '-' && value.size() > 1)
		i++;
	else if (value[0] == '-')
		throw IncorrectValue(value, rawCommand);
	
	for (; i < value.size(); i++)
	{
		if (!isdigit(value[i]))
		{
			if (value[i] == '.' && isFractional(type))
			{
				if (containsDot)
					throw FewDotInNumber(value, rawCommand);
				containsDot = true;
			}
			else if (value[i] == '.')
				throw DotWithIntegerValue(value, rawCommand);
			else
				throw IncorrectValue(value, rawCommand);
		}
	}
	
	return value;
}

CommandList::SyntacticException::SyntacticException(const std::string& strException)
: _strException("Syntactic exception: " + strException)
{
}

const char* CommandList::SyntacticException::what() const throw()
{
	return _strException.c_str();
}

CommandList::IncorrectCommandType::IncorrectCommandType(const std::string& commandType, const std::string& command)
: SyntacticException("command \"" + command + "\", command type '" + commandType + "' is incorrect")
{
}

CommandList::IncorrectValueType::IncorrectValueType(const std::string& valueType, const std::string& command)
: SyntacticException("command \"" + command + "\", value type '" + valueType + "' is incorrect")
{
}

CommandList::IncorrectValue::IncorrectValue(const std::string& value, const std::string& command)
: SyntacticException("command \"" + command + "\", value '" + value + "' is incorrect")
{

}

CommandList::DotWithIntegerValue::DotWithIntegerValue(const std::string& value, const std::string& command)
: SyntacticException("command \"" + command + "\", value '" + value + "' dot with integer value")
{
}

CommandList::FewDotInNumber::FewDotInNumber(const std::string& value, const std::string& command)
: SyntacticException("command \"" + command + "\", value '" + value + "' few dots in number")
{
}

CommandList::NotCorrectExit::NotCorrectExit()
: SyntacticException("program doesn't have an exit instruction or there are instructions after exit")
{
}
