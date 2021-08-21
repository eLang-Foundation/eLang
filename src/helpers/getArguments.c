// an array of arguments will be stored in this variable
strArray getArguments(char *arguments, bool init)
{
	int length = count(',', arguments) + 1;
	char **args = malloc(length * sizeof(char *));

	int argCounter = 0;

	char *argument = malloc(1);
	strcpy(argument, "");

	// the following code splits the arguments string into separate arguments and adds them to the args array
	for (int i = 0, l = (int) strlen(arguments); i < l; i++)
	{
		if ((arguments[i] != ',' && !insideQuotes(i, arguments)) || insideQuotes(i, arguments))
			argument = appendChar(argument, arguments[i]);

		if ((!insideQuotes(i + 1, arguments) && arguments[i + 1] == ',') || (i == l - 1))
		{
			if (strcmp(trim(argument), "") != 0)
			{
				if (init) args[argCounter++] = strdup(trim(argument));
				else
				{
					char *arg = evaluate(trim(argument), true);
					args[argCounter++] = arg;
				}
				free(argument);
				argument = malloc(1);
				strcpy(argument, "");
			}
		}
	}

	free(argument);

	strArray array;
	array.array = args;
	array.length = argCounter;

	return array;
}
