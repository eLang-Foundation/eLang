extern char *get(char *string, char *pattern);
extern bool match(char *string, char *pattern);

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

				// creating a function
				Function f;
				f.name = functionName;
				f.arguments = trim(arguments);
				f.code = trim(code);

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
					char *args[count(',', arguments) + 1];

					int argCounter = 0;
					int charCounter = 0;

					char *argument;
					argument = malloc(0);

					// the following code splits the arguments string into separate arguments and adds them to the args array
					for (int i = 0, l = (int) strlen(arguments); i < l; i++)
					{
						if (arguments[i] != ',')
						{
							char tmp[charCounter + 2];
							strcpy(tmp, argument);
							tmp[charCounter++] = arguments[i];
							argument = realloc(argument, charCounter);
							strcpy(argument, tmp);
						}

						if ((!insideQuotes(i + 1, arguments) && arguments[i + 1] == ',') || (i == l - 1))
						{
							args[argCounter++] = strdup(trim(argument));
							charCounter = 0;
							free(argument);
							argument = malloc(0);
						}
					}

					free(argument);

					for (int i = 0; i < argCounter; i++)
					{
						printf("%s\n", args[i]);
						free(args[i]);
					}
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
