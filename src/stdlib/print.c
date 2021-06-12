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
			string = appendChar(string, ' ');
		}
		else
		{
			char *tmp = evaluate(currentArgument);
			char *convertedToString = toString(getValue(tmp));
			free(tmp);
			if (strcmp(convertedToString, ""))
				string = appendString(string, convertedToString);
			else
				raiseError(INV, "Types other than strings are not supported yet", NULL, 0, FILENAME);
			free(convertedToString);
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
