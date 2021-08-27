#include "re.h"
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

/// \param string The string that needs to be searched
/// \param pattern The regex pattern that will be used while searching for matches in the given string
/// \return The first match of the given pattern in the given string
/// \attention Return value should be freed after usage
/// \author Bekhruz Niyazov
char *get(char *string, char *pattern)
{
	std::string s (string);
	std::regex e (pattern);
	std::smatch m;

	if (std::regex_search(s, m, e))
	{
		char *returnValue = strdup(m.str(1).c_str());
		return returnValue;
	}
	return strdup("");
}

/// \param string The main string to which the pattern will be applied
/// \param pattern The regex pattern using which the match will be checked
/// \return true if the given string matches the given pattern; else false
/// \author Bekhruz Niyazov
bool match(char *string, char *pattern)
{
	std::string s (string);
	std::regex p (pattern);
	bool matched = std::regex_match(s, p);
	return matched;
}
