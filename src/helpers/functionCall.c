// this function does the function call stuff
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
	strArray array = getArguments(trim(arguments));
	char **args = array.array;
	int numberOfArguments = strcmp(arguments, "") ? array.length : 0;

	// if the function name was provided
	if (strcmp(functionName, ""))
	{
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
				}

				// getting the body of the function
				char *code = strdup(currentFunction.code);

				strArray lines = splitIntoLines(code);
				
				for (int i = 0, l = lines.length; i < l; i++)
				{
					char *after = getAfter(lines, i);
					execute(trim(lines.array[i]), after, lineNumber + i + 1);
					free(lines.array[i]);
					free(after);
				}

				free(lines.array);
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
	free(arguments);

	removeLast();
}
