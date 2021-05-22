extern char *get(char *string, char *pattern);

// this function executed the given code
void execute(char *line, char *after, bool ignore)
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
				printf("function name: %s\n", functionName);

				// getting the body of the function
				char *body = getContents(after, '{', '}');
				printf("body: `%s`\n", body);

				// getting the arguments of the function
				char *arguments = get(after, "\\(([\\w\\W]*?)\\)\\s*\\{");
				printf("arguments: %s\n", arguments);

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
