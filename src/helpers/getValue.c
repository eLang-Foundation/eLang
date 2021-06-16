// this function returns the value of the given string
char *getValue(char *string)
{
	for (int i = 0; i < numberOfVariables; i++)
	{
		if (!strcmp(VARIABLES[i].name, string))
		{
			char *scope = strdup(VARIABLES[i].scope);
			scope = appendString(scope, "[\\w\\W]*");
			if (match(SCOPE, scope))
			{
				free(scope);
				return VARIABLES[i].value;
			}
			free(scope);
		}
	}

	char *tmp = evaluate(string);

	if (strcmp(type(tmp), "Undefined"))
	{
		free(tmp);
		return string;
	}

	free(tmp);

	char error[] = "Name \"";
	strcat(error, string);
	strcat(error, "\" is not defined");
	raiseError(NND, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
	return NULL;
}
