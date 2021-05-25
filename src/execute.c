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
		}
		// if a function was called
		else if (match(trim(after), "[\\w\\d_]+\\s*\\([\\w\\W]*\\)[\\w\\W]*"))
		{
			puts(line);
			char *functionName = get(after, "([\\w\\d]+)\\s*\\(");
			puts(functionName);

			free(functionName);
		}
	}

	for (int i = 0; i < counter; i++)
	{
		free(words[i]);
	}

}
