#include "../../tests/append.h"

/// \param string The given string
/// \param chr The given character
/// \return The given string with given character at the end
/// \attention Return value should be freed after usage
/// \author Bekhruz Niyazov
char *appendChar(char *string, char chr)
{
	size_t length = strlen(string);
	char tmp[length + 2];
	strcpy(tmp, string);
	tmp[length++] = chr;
	tmp[length] = '\0';
	free(string);
	return strdup(tmp);
}

/// \param string The first string
/// \param string2 The second string
/// \return The first string with the second string appended at the end
/// \attention 1. string1 parameter should be a pointer to an allocated memory
/// \attention 2. Return value should be freed after usage
/// \author Bekhruz Niyazov
char *appendString(char *string, char *string2)
{
	size_t length = strlen(string);
	size_t length2 = strlen(string2);
	char tmp[length + length2 + 1];
	strcpy(tmp, string);
	for (int i = 0; i < length2; i++)
	{
		tmp[length++] = string2[i];
	}
	tmp[length] = '\0';
	free(string);
	return strdup(tmp);
}

/// \param functions A pointer to an array of variables of type Function
/// \param function A variable of type Function
/// \return functions with function appended at the end
/// \author Bekhruz Niyazov
Function *appendFunction(Function *functions, Function function)
{
	if (match(function.name, "[\\d\\.]+"))
	{
		char error[] = "Couldn't use name \"";
		strcat(error, function.name);
		strcat(error, "\" as a function name");
		raiseError(INS, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
	}

	Function tmp[numberOfFunctions + 1];

	for (int i = 0; i < numberOfFunctions; i++)
	{
		tmp[i] = functions[i];
	}
	tmp[numberOfFunctions++] = function;

	functions = realloc(functions, numberOfFunctions * sizeof(Function));

	for (int i = 0; i < numberOfFunctions; i++)
	{
		functions[i] = tmp[i];
	}

	return functions;
}

/// \param variables A pointer to an array of variables of type Variable
/// \param variable A variable of type Variable
/// \return variables with variable appended at the end
/// \author Bekhruz Niyazov
Variable *appendVariable(Variable *variables, Variable variable)
{
	if (match(variable.name, "[\\d\\.]+"))
	{
		char error[] = "Couldn't use name \"";
		strcat(error, variable.name);
		strcat(error, "\" as a variable name");
		raiseError(INS, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
	}

	Variable tmp[numberOfVariables + 1];

	for (int i = 0; i < numberOfVariables; i++)
	{
		tmp[i] = variables[i];
	}
	tmp[numberOfVariables++] = variable;

	variables = realloc(variables, numberOfVariables * sizeof(Variable));

	for (int i = 0; i < numberOfVariables; i++)
	{
		variables[i] = tmp[i];
	}

	return variables;
}
