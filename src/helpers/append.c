#include "../../tests/append.h"

// this function appends the given character to the given string
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

// this function appends the given Variable to the given Variables array
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

	variables = realloc(variables, numberOfVariables * sizeof(Function));

	for (int i = 0; i < numberOfVariables; i++)
	{
		variables[i] = tmp[i];
	}

	return variables;
}
