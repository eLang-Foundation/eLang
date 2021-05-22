extern char *get(char *string, char *pattern);

// this function executed the given code
void execute(char *line, char *after, int *functionCount)
{
	int counter = 0;
	char *token = strtok(line, " ");

	// getting the size of the array
	while (token != NULL)
	{
		counter++;
		token = strtok(NULL, " ");
	}

	// creating an array of words
	char *words[counter];
	token = strtok(line, " ");
	counter = 0;

	// filling in the array of words
	while (token != NULL)
	{
		words[counter++] = strdup(token);
		token = strtok(NULL, " ");
	}

	char *functionKeyword = "function";

	if (counter)
	{
		if (!ignore)
		{
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
				f.code= trim(code);

				// appending the function to the array of functions
				FUNCTIONS[*functionCount] = f;
				// incrementing the number of functions
				*functionCount = (*functionCount + 1);

				// checking if the next line of code is inside of a function
				bool found = false;
				for (int i = 0, l = (int) strlen(code); i < l; i++)
				{
					if (code[i] == '\n') found = true;
				}
				// if it is then ignore the next line
				ignore = found ? true : false;

				free(functionName);
				free(code);
				free(arguments);
			}
		}
	}

	for (int i = 0; i < counter; i++)
	{
		free(words[i]);
	}

}
