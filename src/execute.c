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
				char *functionName = get(after, "function\\s+([\\w_\\d]+)\\s*\\(");

				// getting the body of the function
				char *body = get(after, "\\{([\\w\\W]*)\\}");
				char bodyWithoutWhitespaces[strlen(body)];
				int charCounter = 0;
				token = strtok(body, "\n");
				while (token != NULL)
				{
					char *withoutWhitespaces = removeWhitespace(token);
					for (int i = 0, l = (int) strlen(withoutWhitespaces); i < l; i++)
					{
						bodyWithoutWhitespaces[charCounter++] = withoutWhitespaces[i];
					}
					free(withoutWhitespaces);
					token = strtok(NULL, "\n");
				}
				free(functionName);
				free(body);
			}
		}
	}

	for (int i = 0; i < counter; i++)
	{
		free(words[i]);
	}

}
