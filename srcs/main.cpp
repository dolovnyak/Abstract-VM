#include <iostream>
#include <fstream>
#include "CommandList.hpp"

void addCommand(CommandList& commandList, std::list<std::string>& lexicalExceptionList, const std::string& command)
{
	try
	{
		commandList.AddCommand(command);
	}
	catch (const std::exception& exception)
	{
		lexicalExceptionList.emplace_back(exception.what());
	}
}

void runCommands(CommandList& commandList, std::list<std::string>& lexicalExceptionsList)
{
	if (lexicalExceptionsList.empty())
	{
		try
		{
			commandList.Execute();
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
		}
	}
	else
	{
		std::cout << std::endl <<
		"The assembly program includes one or several lexical errors or syntactic errors:" <<
		std::endl << std::endl;
		
		for (const std::string& lexicalException : lexicalExceptionsList)
			std::cout << std::string(5, ' ') << lexicalException << std::endl;
	}
}

void runFromStandardOutput()
{
	CommandList commandList;
	std::list<std::string> lexicalExceptionList;
	std::string command;
	
	while (true)
	{
		std::getline(std::cin, command);
		
		//TODO string with only spaces equal empty string
		if (command.empty() || (command[0] == ';' && command != ";;"))
			continue;
		if (command == ";;")
			break;
		
		addCommand(commandList, lexicalExceptionList, command);
	}
	runCommands(commandList, lexicalExceptionList);
}

void runFromFile(char* filePath)
{
	std::ifstream inputFile;
	inputFile.open(filePath);
	
	if (!inputFile.is_open())
	{
		std::cout << "input file name doesn't correct" << std::endl;
		return;
	}
	
	CommandList commandList;
	std::list<std::string> lexicalExceptionList;
	std::string command;
	
	while (std::getline(inputFile, command))
	{
		if (command.empty() || command[0] == ';')
			continue;
		addCommand(commandList, lexicalExceptionList, command);
	}
	
	runCommands(commandList, lexicalExceptionList);
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		runFromStandardOutput();
	}
	else if (argc == 2)
	{
		runFromFile(argv[1]);
	}
	else
		std::cout << "incorrect number of arguments" << std::endl;
	
	return 0;
}
