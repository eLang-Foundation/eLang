// this function removes the last element of the SCOPE
void removeLast(void)
{
	char *blocks[count('>', SCOPE)];

	char *token = strtok(SCOPE, " -> ");

	int index = 0;

	while (token != NULL)
	{
		blocks[index++] = strdup(token);
		token = strtok(NULL, " -> ");
	}

	if (index > 0)
	{
		char *newScope = strdup("");

		for (int i = 0; i < index - 1; i++)
		{
			newScope = appendString(newScope, " -> ");
			newScope = appendString(newScope, blocks[i]);
			free(blocks[i]);
		}
		free(blocks[index - 1]);

		free(SCOPE);
		SCOPE = strdup(newScope);
		free(newScope);
	}
}

// this function removes the last variable from the array of variables
void removeVariable(Variable variable)
{
	int counter = 0;
	for (ui i = 0; i < numberOfVariables; i++)
	{
		if (strcmp(VARIABLES[i].name, variable.name) || strcmp(VARIABLES[i].scope, variable.scope))
		{
			VARIABLES[counter++] = VARIABLES[i];
		}
	}
	numberOfVariables = counter;
}
