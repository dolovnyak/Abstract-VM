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
	Lexer();
	Lexer(const Lexer& lexer);
	Lexer& operator=(const Lexer& lexer);
	~Lexer();
	
	void ParseIntoLexemes(const std::string& command);
	std::vector<Lexeme> GetLexemes() const;

private:
	std::vector<Lexeme> _lexemes;
};
