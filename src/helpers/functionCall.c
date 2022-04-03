/// \param line Line of code on which the function call is located
/// \param after Code after the line (including the line)
/// \author	Bekhruz Niyazov
void functionCall(char *line, char *after)
{
	// if the function was just a part of a string and not a function
	if (insideQuotes(getIndex(line, '('), line))
	{
		return;
	}

	char *functionName = get(line, "([\\w\\d]+)\\s*\\(");
	char *arguments = get(after, "\\(([\\w\\W]*)\\)");

	SCOPE = appendString(SCOPE, " -> ");
	SCOPE = appendString(SCOPE, functionName);

	bool definedByUser = false;
	bool eLangFunction = false;

	// an array of arguments will be stored in this variable
	strArray array = getArguments(trim(arguments), false);
	char **args = array.array;
	int numberOfArguments = strcmp(arguments, "") ? array.length : 0;

	// if the function name was provided
	if (strcmp(functionName, "") != 0)
	{
		// creating an array that will store the variables in the function
		Variable *variables = calloc(1, sizeof(Variable));
		int variableCounter = 0;

		// if the function was defined by the user
		for (int j = 0; j < numberOfFunctions; j++)
		{
			Function currentFunction = FUNCTIONS[j];
			if (!strcmp(functionName, currentFunction.name))
			{
				if (numberOfArguments != currentFunction.argumentsNumber)
				{
					char error[] = "Expected ";
					char expected[2];
					sprintf(expected, "%i", currentFunction.argumentsNumber);
					strcat(error, expected);
					strcat(error, " arguments, got ");
					char got[2];
					sprintf(got, "%i", numberOfArguments);
					strcat(error, got);
					raiseError(INV, error, line, lineNumber, FILENAME);
				}

				definedByUser = true;

				// making the given arguments variables
				for (int i = 0; i < numberOfArguments; i++)
				{
					Variable var;
					var.name = strdup(currentFunction.arguments[i]);
					var.value = strdup(args[i]);
					var.type = type(args[i]);
					var.scope = strdup(SCOPE);

					VARIABLES = appendVariable(VARIABLES, var);

					variables = realloc(variables, sizeof(Variable) * ++variableCounter);
					variables[variableCounter - 1] = var;
				}

				// getting the body of the function
				char *code = strdup(currentFunction.code);

				strArray lines = splitIntoLines(code);

				bool returned = false;

				for (int i = 0; i < lines.length; i++)
				{
					char *innerAfter = getAfter(lines, i);

					char *tmp = strdup(lines.array[i]);
					char *lineCopy = trim(tmp);

					execute(lineCopy, innerAfter, lineNumber + i + 1);

					char *first = strtok(lineCopy, " ");
					if (first && !strcmp(first, "return")) returned = true;

					free(tmp);
					free(lines.array[i]);
					free(innerAfter);
				}

				if (!returned)
				{
					free(lastReturnValue);
					lastReturnValue = strdup("Null");
				}

//				free(lines.array);
				free(code);

				break;
			}
		}

		// if function is an eLang function
		if (!definedByUser)
		{
			for (int j = 0; j < numberOfeLangFunctions; j++)
			{
				if (!strcmp(functionName, ELANG_FUNCTIONS[j]))
				{
					eLangFunction = true;

					if (!strcmp(functionName, "print"))
					{
						print(args, numberOfArguments);
						break;
					}

					if (!strcmp(functionName, "println"))
					{
						println(args, numberOfArguments);
						break;
					}
				}
			}
		}

		for (int i = 0; i < variableCounter; i++)
		{
			removeVariable(variables[i]);
			free(variables[i].name);
			free(variables[i].value);
			free(variables[i].scope);
		}
		free(variables);
	}

	for (int i = 0; i < numberOfArguments; i++)
	{
		free(args[i]);
	}
	free(args);

	// if function is not defined
	if (!definedByUser && !eLangFunction)
	{
		char error[] = "\"";
		strcat(error, functionName);
		strcat(error, "\" is not defined");
		raiseError(FND, error, line, lineNumber, FILENAME);
	}

	free(functionName);
//	free(arguments);

	removeLast();
}
