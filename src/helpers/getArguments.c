/// \param arguments Arguments of the function
/// \param init I have no idea what that is; gotta check that later
/// \return An array of strings each of which represents an argument
/// \author Bekhruz Niyazov
strArray getArguments(char *arguments, bool init)
{
	int length = count(',', arguments) + 1;
	char **args = malloc(length * sizeof(char *));

	int argCounter = 0;

	char *argument = strdup("");

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
					char *arg = evaluate(trim(argument), true, false);
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
