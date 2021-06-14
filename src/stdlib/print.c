void print(char **args, int numberOfArguments)
{
	// this string will be printed
	char *string = strdup("");

	for (int k = 0; k < numberOfArguments; k++)
	{
		char *currentArgument = args[k];

		currentArgument = getValue(currentArgument);

		if (!strcmp(type(currentArgument), "String"))
		{
			char *tmp = convertValueToString(currentArgument);
			string = appendString(string, tmp);
			free(tmp);
		}
		else
		{
			char *tmp = evaluate(currentArgument);
			if (strcmp(tmp, ""))
			{
				char *convertedToString = toString(getValue(tmp));
				free(tmp);
				if (strcmp(convertedToString, ""))
				{
					string = appendString(string, convertedToString);
					free(convertedToString);
				}
				else
				{
					free(convertedToString);
					char error[] = "Name \"";
					strcat(error, currentArgument);
					strcat(error, "\" is not defined");
					raiseError(INS, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
				}
			}
			else
				free(tmp);
		}
	}

	printf("%s", string);
	free(string);
}

void println(char **args, int numberOfArguments)
{
	print(args, numberOfArguments);
	printf("\n");
}
