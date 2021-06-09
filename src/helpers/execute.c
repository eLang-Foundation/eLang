// this function executed the given code
void execute(char *line, char *after, int lineNumber)
{
	if (line[0] == ';') return;

	char lineCopy[strlen(line) + 1];
	strcpy(lineCopy, line);
	char *firstWord = strtok(lineCopy, " ");

	char *functionKeyword = "fun";

	if (firstWord)
	{
		if (!ignore)
		{
			// if a function was defined
			if (!strcmp(firstWord, functionKeyword))
			{
				if (numberOfFunctions == 0)
				{
					FUNCTIONS = malloc(1 * sizeof(Function));
				}
				
				// getting the name of the function
				char *functionName = get(line, "fun\\s+([\\w_\\d]+)\\s*[\\(\\{]+");

				// getting the code inside of the function
				char *code = getContents(after, '{', '}');

				// getting the arguments of the function
				char *arguments = getContents(line, '(', ')');

				strArray array = getArguments(trim(arguments));

				// creating a function
				Function f;
				f.name = strdup(trim(functionName));
				f.arguments = array.array;
				f.code = strdup(trim(code));
				f.argumentsNumber = strcmp(arguments, "") ? array.length : 0;

				// appending the function to the array of functions
				FUNCTIONS = appendFunction(FUNCTIONS, f);

				// checking if the next line of code is inside of a function
				ignore = false;
				for (int i = 0, l = (int) strlen(code); i < l; i++)
				{
					if (code[i] == '\n')
					{
						ignore = true;
						break;
					}
				}

				free(functionName);
				free(code);
				free(arguments);
			}

			// if a function was called
			else if (match(line, "[\\w\\d_]+\\s*\\([\\w\\W]*\\)[\\w\\W]*"))
			{
				// if the function was just a part of a string and not a function
				if (insideQuotes(getIndex(line, '('), line))
				{
					return;
				}

				char *functionName = get(line, "([\\w\\d]+)\\s*\\(");
				char *arguments = get(after, "\\(([\\w\\W]*?)\\)");

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

							// getting the body of the function
							char *code = strdup(currentFunction.code);

							if (strcmp(arguments, ""))
							{
								// replacing the argument variables with given arguments
								for (int k = 0; k < numberOfArguments; k++)
								{
									char *arg = currentFunction.arguments[k];
									char *tmp = replace(code, arg, args[k]);
									free(code);
									code = strdup(tmp);
									free(tmp);
								}
							}

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
			}

			// if a variable was created or changed
			else if (match(line, "[\\w_\\d]+\\s*=\\s*[\\w\\W]+"))
			{
				if (numberOfVariables == 0)
				{
					VARIABLES = malloc(1 * sizeof(Variable));
				}

				char *varName = get(line, "([\\w_\\d]+?)\\s*=");
				char *varValue = get(line, "[\\w_\\d]+\\s*=\\s*([\\w\\W]+)");

				bool exists = false;

				for (int i = 0; i < numberOfVariables; i++)
				{
					if (!strcmp(VARIABLES[i].name, varName))
					{
						free(VARIABLES[i].value);
						VARIABLES[i].value = strdup(varValue);
						exists = true;
						break;
					}
				}

				if (!exists)
				{
					// creating a variable
					Variable var;
					var.name = strdup(varName);
					var.value = strdup(varValue);
					var.type = type(varValue);

					// appending the variable to the array of variables
					VARIABLES = appendVariable(VARIABLES, var);
				}

				free(varName);
				free(varValue);
			}

			// if the following code is an if statement
			else if (!strcmp(firstWord, "if"))
			{
				char *expression = trim(get(line, "if\\s+([\\w\\W]+)\\s*\\{"));

				char *code = getContents(after, '{', '}');

				if (!strcmp(toBool(expression), "false"))
				{
					// checking if the next line of code is inside of a function
					ignore = false;
					for (int i = 0, l = (int) strlen(code); i < l; i++)
					{
						if (code[i] == '\n')
						{
							ignore = true;
							break;
						}
					}
				}

				free(expression);
				free(code);
			}

			// invalid syntax
			else if (strcmp(line, "}"))
			{
				raiseError(ERROR_MSG, INS, line, lineNumber, FILENAME);
			}
		}
	}
}

