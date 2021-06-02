void print(char **args, int numberOfArguments)
{
	for (int k = 0; k < numberOfArguments; k++)
	{
		char *currentArgument = args[k];

		// this string will be printed
		char *string = malloc(1);
		strcpy(string, "");

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
		}

		printf("%s", string);
	}
}

void println(char **args, int numberOfArguments)
{
	print(args, numberOfArguments);
	printf("\n");
}
