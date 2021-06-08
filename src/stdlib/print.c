void print(char **args, int numberOfArguments)
{
	// this string will be printed
	char *string = malloc(1);
	strcpy(string, "");

	for (int k = 0; k < numberOfArguments; k++)
	{
		char *currentArgument = args[k];

		int length = (int) strlen(currentArgument);

		int index = length - 1;

		if ((currentArgument[0] == '"' && currentArgument[index] == '"') ||
			(currentArgument[0] == '\'' && currentArgument[index] == '\'') ||
			(currentArgument[0] == '`' && currentArgument[index] == '`'))
		{
			for (int h = 1, l = length; h < l - 1; h++)
			{
				string = appendChar(string, currentArgument[h]);
			}
			if (k < numberOfArguments - 1) string = appendChar(string, ' ');
		}
		else
		{
			if (strcmp(currentArgument, ""))
				raiseError(INV, "Types other than strings are not supported yet", NULL, 0, FILENAME);
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
