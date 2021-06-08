#include "../../tests/append.h"

// this function appends the given character to the given string
char *appendChar(char *string, char chr)
{
	size_t length = strlen(string);
	char tmp[length + 2];
	strcpy(tmp, string);
	tmp[length++] = chr;
	tmp[length++] = '\0';
	free(string);
	return strdup(tmp);
}

// this function appends the given string to the given string
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
	tmp[length++] = '\0';
	string = realloc(string, length);
	strcpy(string, tmp);
	return string;
}

// this function appends the given Function to the given Functions array
Function *appendFunction(Function *functions, Function function, int functionCount)
{
	Function tmp[functionCount + 1];

	for (int i = 0; i < functionCount; i++)
	{
		tmp[i] = functions[i];
	}
	tmp[functionCount++] = function;

	functions = realloc(functions, functionCount * sizeof(Function));

	for (int i = 0; i < functionCount; i++)
	{
		functions[i] = tmp[i];
	}

	return functions;
}

// this function appends the given Variable to the given Variables array
Variable *appendVariable(Variable *variables, Variable variable, int variableCount)
{
	Variable tmp[variableCount + 1];

	for (int i = 0; i < variableCount; i++)
	{
		tmp[i] = variables[i];
	}
	tmp[variableCount++] = variable;

	variables = realloc(variables, variableCount * sizeof(Function));

	for (int i = 0; i < variableCount; i++)
	{
		variables[i] = tmp[i];
	}

	return variables;
}
