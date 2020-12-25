#pragma once

#include "AbstractVmStack.hpp"
#include <list>
#include <vector>


class CommandList
{
public:
	//TODO add coplien form
	void AddCommand(std::string command);
	void Execute();
	
private:
	enum CommandType
	{
		Push = 0,
		Pop,
		Dump,
		Assert,
		Add,
		Sub,
		Mul,
		Div,
		Modulo,
		Print,
		Exit,
	};
	typedef struct	Command
	{
		CommandType commandType;
		OperandType operandType;
		std::string value;
	}				Command;
	
	std::list<Command> _commandList;
	
	OperandType GetOperandType(const std::string& strOperandType);
	std::string GetOperandValue(const std::string& operandValue);
	void AddCommandWithoutValue(const std::string& strCommand);
	void AddCommandWithValue(const std::vector<std::string>& commandWords);
};

