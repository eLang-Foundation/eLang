// this function returns the value of the given string
char *getValue(char *string)
{
	for (int i = 0; i < numberOfVariables; i++)
	{
		if (!strcmp(VARIABLES[i].name, string))
		{
			return VARIABLES[i].value;
		}
	}

	return string;
}
