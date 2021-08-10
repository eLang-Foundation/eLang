/// \param args Arguments to be printed
/// \param numberOfArguments Number of given arguments
/// \author Bekhruz Niyazov
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
			free(currentArgument);
		}
		else
		{
			char *convertedToString = toString(currentArgument);
			free(currentArgument);
			if (strcmp(convertedToString, "") != 0)
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
	}

	printf("%s", string);
	free(string);
}

/// \param args Arguments to be printed
/// \param numberOfArguments Number of given arguments
/// \author Bekhruz Niyazov
void println(char **args, int numberOfArguments)
{
	print(args, numberOfArguments);
	printf("\n");
}
