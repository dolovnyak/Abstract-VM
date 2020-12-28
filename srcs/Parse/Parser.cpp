#include "Parser.hpp"

std::string to_string(const Token& token)
{
	switch (token)
	{
		case Token::Word:			return "word";
		case Token::OpenBracket:	return "(";
		case Token::CloseBracket:	return ")";
	}
}

std::string to_string(const std::vector<Lexeme>& lexemes)
{
	std::string strLexemes;
	
	for (Lexeme lexeme : lexemes)
	{
		strLexemes += to_string(lexeme.token) + " ";
	}
	if (!strLexemes.empty())
		strLexemes.erase(strLexemes.size() - 1);
	
	return strLexemes;
}

Parser::Parser(const std::vector<Lexeme>& lexemes, const std::string& rawCommand)
: _lexemes(lexemes), _rawCommand(rawCommand)
{
}

void Parser::ParseLexemes()
{
	if (_lexemes.size() == 1 && _lexemes.front().token == Token::Word)
	{
		_instructionType = InstructionType::CommandWithoutValue;
		_commandType = _lexemes.front().str;
	}
	else if (_lexemes.size() == 5 &&
		_lexemes[0].token == Token::Word &&
		_lexemes[1].token == Token::Word &&
		_lexemes[2].token == Token::OpenBracket &&
		_lexemes[3].token == Token::Word &&
		_lexemes[4].token == Token::CloseBracket)
	{
		_instructionType = InstructionType::CommandWithValue;
		_commandType = _lexemes[0].str;
		_valueType = _lexemes[1].str;
		_value = _lexemes[3].str;
	}
	else
		throw LexicalException(_lexemes, _rawCommand);
}

InstructionType Parser::GetInstructionType() const
{
	return _instructionType;
}

std::string Parser::GetCommandType() const
{
	return _commandType;
}

std::string Parser::GetValueType() const
{
	return _valueType;
}

std::string Parser::GetValue() const
{
	return _value;
}

Parser::LexicalException::LexicalException(const std::vector<Lexeme>& lexemes, const std::string rawCommand)
: _strException("Lexical exception: command \"" + rawCommand +
	"\", correct lexemes \"word\" or \"word word ( word )\", your lexemes \"" + to_string(lexemes) + "\"")
{
}

const char* Parser::LexicalException::what() const throw()
{
	return _strException.c_str();
}
