// this function converts the given variable to string
char *toString(char *var)
{
	for (int i = 0; i < numberOfVariables; i++)
	{
		Variable currentVariable = VARIABLES[i];

		if (!strcmp(currentVariable.name, var))
		{
			if (!strcmp(type(currentVariable.value), "string"))
			{
				return convertValueToString(currentVariable.value);
			}

		}
	}

	if (numberable(var))
	{
		return strdup(var);
	}

	if (!strcmp(type(var), "string"))
	{
		return convertValueToString(var);
	}

	return strdup("");
}
