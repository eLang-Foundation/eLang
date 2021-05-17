#include "get.h"
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

// this function returns the string found using given regex pattern
char *get(char *string, char *pattern)
{
	std::string s (string);
	std::regex e (pattern);
	std::smatch m;

	if (std::regex_search(s, m, e))
	{
		char returnValue[m.str(1).length()];
		strcpy(returnValue, m.str(1).c_str());
		return strdup(returnValue);
	}
	return strdup("");
}
