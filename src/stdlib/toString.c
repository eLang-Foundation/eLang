// this function converts the given variable to string
char *toString(char *var, int numberOfVariables)
{
	for (int i = 0; i < numberOfVariables; i++)
	{
		Variable currentVariable = VARIABLES[i];
		if (!strcmp(currentVariable.name, var))
		{
			if (!strcmp(type(currentVariable.value), "string"))
			{
				char *string = malloc(1);
				strcpy(string, "");
				for (int h = 1, l = strlen(currentVariable.value); h < l - 1; h++)
				{
					string = appendChar(string, currentVariable.value[h]);
				}
				return string;
			}

			else if (numberable(currentVariable.value))
			{
				return strdup(currentVariable.value);
			}
		}
	}

	return strdup("");
}
