#pragma once

#include <string>
#include <vector>

enum Token
{
	Word = 0,
	OpenBracket,
	CloseBracket
};

typedef struct Lexeme
{
	Token token;
	std::string str;
}	Lexeme;

class Lexer
{
public:
	//TODO coplien form
	void ParseIntoLexemes(const std::string& command);
	std::vector<Lexeme> GetLexemes() const;

private:
	std::vector<Lexeme> _lexemes;
};
