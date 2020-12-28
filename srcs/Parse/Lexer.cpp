#include "Lexer.hpp"

static bool isWordCharacter(char c)
{
	if (isprint(c) && c != '(' && c != ')' && c != ' ')
		return true;
	
	return false;
}

static std::string parseWord(int i, const std::string& command)
{
	int startWord = i;
	i++;
	
	while (command[i] && isWordCharacter(command[i]))
		i++;
	
	return command.substr(startWord, i - startWord);
}

void Lexer::ParseIntoLexemes(const std::string& command)
{
	int i = 0;
	
	while (command[i])
	{
		if (isWordCharacter(command[i]))
		{
			Lexeme lexeme;
			lexeme.token = Token::Word;
			lexeme.str = parseWord(i, command);
			i += lexeme.str.size() - 1;
			_lexemes.push_back(lexeme);
		}
		else if (command[i] == '(')
		{
			Lexeme lexeme;
			lexeme.token = Token::OpenBracket;
			_lexemes.push_back(lexeme);
		}
		else if (command[i] == ')')
		{
			Lexeme lexeme;
			lexeme.token = Token::CloseBracket;
			_lexemes.push_back(lexeme);
		}
		i++;
	}
}

std::vector<Lexeme> Lexer::GetLexemes() const
{
	return _lexemes;
}
