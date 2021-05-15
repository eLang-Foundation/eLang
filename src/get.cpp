#include <regex>
#include "get.h"
#include <iostream>
#include <cstring>

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if(start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

// this function returns the string found using given regex pattern
char *get(char *string, char *pattern)
{
	std::string s (string);
	std::regex e (pattern);
	std::smatch m;
	std::string returnString = s;

	while (std::regex_search(s, m, e))
	{
		std::cout << std::endl;
		s = m.suffix().str();

	}

	replace(returnString, s, "");

	char returnValue[returnString.length()];

	strcpy(returnValue, returnString.c_str());

	return strdup(&returnValue[0]);
}
