extern char *get(char *, char *);
extern bool match(char *, char *);

// this function executed the given code
void execute(char *line, char *after, int *functionCount)
{
	int counter = 0;

	char *lineCopy = strdup(line);
	char *token = strtok(lineCopy, " ");

	// getting the size of the array
	while (token != NULL)
	{
		counter++;
		token = strtok(NULL, " ");
	}
	free(lineCopy);

	// creating a copy of the line
	lineCopy = strdup(line);

	// creating an array of words
	char *words[counter];

	token = strtok(lineCopy, " ");
	counter = 0;
	// filling in the array of words
	while (token != NULL)
	{
		words[counter++] = strdup(token);
		token = strtok(NULL, " ");
	}

	free(lineCopy);

	char *functionKeyword = "function";

	if (counter)
	{
		if (!ignore)
		{
			// if a function was defined
			if (!strcmp(words[0], functionKeyword))
			{
				// getting the name of the function
				char *functionName = get(after, "function\\s+([\\w_\\d]+)\\s*[\\(\\{]+");

				// getting the code inside of the function
				char *code = getContents(after, '{', '}');

				// getting the arguments of the function
				char *arguments = get(after, "\\(([\\w\\W]*?)\\)\\s*\\{");

				strArray array = getArguments(trim(arguments));
				
				// creating a function
				Function f;
				f.name = strdup(trim(functionName));
				f.arguments = array.array;
				f.code = strdup(trim(code));
				f.argumentsNumber = array.length;

				// appending the function to the array of functions
				FUNCTIONS[*functionCount] = f;
				// incrementing the number of functions
				*functionCount = (*functionCount + 1);

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
					return;

				char *functionName = get(line, "([\\w\\d]+)\\s*\\(");
				char *arguments = get(after, "\\(([\\w\\W]*?)\\)");

				if (strcmp(arguments, ""))
				{
					// an array of arguments will be stored in this variable
					strArray array = getArguments(arguments);
					char **args = array.array;

					// if the function name was provided
					if (strcmp(functionName, ""))
					{
						Function function;
						char *code;
						// if the function was defined by the user
						bool definedByUser = false;
						for (int j = 0; j < *functionCount; j++)
						{
							Function currentFunction = FUNCTIONS[j];
							if (!strcmp(functionName, currentFunction.name))
							{
								definedByUser = true;

								// getting the body of the function
								code = strdup(currentFunction.code);

								// replacing the argument variables with given arguments
								for (int k = 0, n = currentFunction.argumentsNumber; k < n; k++)
								{
									char *arg = currentFunction.arguments[k];
									
								}

								// puts(code);
								free(code);
								break;
							}
						}
					}

					for (int i = 0; i < count(',', arguments) + 1; i++)
					{
						free(args[i]);
					}
					free(args);
				}

				free(functionName);
				free(arguments);
			}
		}
	}

	for (int i = 0; i < counter; i++)
	{
		free(words[i]);
	}

}
