#pragma once

#include "Lexer.hpp"
#include "CommandList.hpp"

enum InstructionType
{
	CommandWithValue = 0,	// word
	CommandWithoutValue		// word word ( word )
};

class Parser
{
public:
	Parser();
	Parser(const std::vector<Lexeme>& lexemes, const std::string& rawCommand);
	Parser(const Parser& parser);
	Parser& operator=(const Parser& parser);
	~Parser();
	
	void ParseLexemes();
	
	InstructionType GetInstructionType() const;
	std::string GetCommandType() const;
	std::string GetValueType() const;
	std::string GetValue() const;

private:
	const std::vector<Lexeme> _lexemes;
	const std::string _rawCommand;
	InstructionType _instructionType;
	std::string _commandType;
	std::string _valueType;
	std::string _value;
	
	class LexicalException : public std::exception
	{
	public:
		LexicalException(const std::vector<Lexeme>& lexemes, const std::string rawCommand);
		const char* what() const throw() override;
	
	private:
		std::string _strException;
	};
};


