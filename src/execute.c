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
				char *returnValue = get(after, "function\\s+([\\w_\\d]+)\\s*");
				printf("return value: %s\n", returnValue);
				free(returnValue);
			}
		}
	}

	for (int i = 0; i < counter; i++)
	{
		free(words[i]);
	}

}
