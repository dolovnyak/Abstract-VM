#pragma once

#include <iostream>
#include <sstream>

#define TEXT_RED std::string("\e[91m")
#define TEXT_GREEN std::string("\e[92m")
#define TEXT_YELLOW std::string("\e[93m")
#define TEXT_MAGENTA std::string("\e[95m")
#define TEXT_CYAN std::string("\e[96m")
#define TEXT_BLACK std::string("\e[30m")
#define TEXT_DEFAULT std::string("\e[39m")
#define BG_RED std::string("\e[41m")
#define BG_YELLOW std::string("\e[43m")
#define BG_GREEN std::string("\e[42m")
#define BG_GRAY std::string("\e[47m")
#define BG_CYAN std::string("\e[46m")
#define BG_DEFAULT std::string("\e[49m")

template<typename T>
void Print_Success(T val)
{
	std::cout << TEXT_GREEN + BG_DEFAULT;
	std::cout << val << std::endl;
	std::cout << TEXT_DEFAULT + BG_DEFAULT;
};

template <typename T>
std::string to_string_precision(const T a_value, const int n = 100)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}

bool contains(const std::string& orig, const std::string& income);