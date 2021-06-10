void print(char **args, int numberOfArguments)
{
	// this string will be printed
	char *string = malloc(1);
	strcpy(string, "");

	for (int k = 0; k < numberOfArguments; k++)
	{
		char *currentArgument = args[k];

		currentArgument = getValue(currentArgument);

		if (!strcmp(type(currentArgument), "String"))
		{
			free(string);
			string = convertValueToString(currentArgument);
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
