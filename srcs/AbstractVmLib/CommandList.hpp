#pragma once

#include "AbstractVmStack.hpp"
#include "Parser.hpp"
#include <list>
#include <vector>

class CommandList
{
public:
	CommandList();
	CommandList(const CommandList& commandList);
	CommandList& operator=(const CommandList& commandList);
	~CommandList();
	
	void AddCommand(const std::string& command);
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
		OperandType valueType;
		std::string value;
	}				Command;
	
	std::list<Command> _commandList;
	
	OperandType GetValueType(const std::string& strValueType, const std::string& rawCommand);
	std::string GetValue(const std::string& value, OperandType type, const std::string& rawCommand);
	void AddCommandWithoutValue(const std::string& commandType, const std::string& rawCommand);
	void AddCommandWithValue(const std::string& commandType, const std::string& valueType,
						  const std::string& value, const std::string& rawCommand);
	
	class SyntacticException : public std::exception
	{
	public:
		SyntacticException(const std::string& strException);
		const char* what() const throw() override;
	
	private:
		const std::string _strException;
	};
	
	class IncorrectCommandType : public SyntacticException
	{
	public:
		IncorrectCommandType(const std::string& commandType, const std::string& command);
	};
	
	class IncorrectValueType : public SyntacticException
	{
	public:
		IncorrectValueType(const std::string& valueType, const std::string& command);
	};
	
	class IncorrectValue : public SyntacticException
	{
	public:
		IncorrectValue(const std::string& valueType, const std::string& command);
	};
	
	class DotWithIntegerValue : public SyntacticException
	{
	public:
		DotWithIntegerValue(const std::string& value, const std::string& command);
	};
	
	class FewDotInNumber : public SyntacticException
	{
	public:
		FewDotInNumber(const std::string& value, const std::string& command);
	};
	
	class NotCorrectExit : public SyntacticException
	{
	public:
		NotCorrectExit();
	};
};

