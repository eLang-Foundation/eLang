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
				return strdup(VARIABLES[i].value);
			}
			free(scope);
		}
	}

	char *tmp = evaluate(string, true);
	if (strcmp(type(tmp), "Undefined"))
	{
		return tmp;
	}

	free(tmp);

	char error[] = "Name \"";
	strcat(error, string);
	strcat(error, "\" is not defined");
	raiseError(NND, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
	return NULL;
}
