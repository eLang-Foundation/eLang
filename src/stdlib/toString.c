// this function converts the given variable to string
char *toString(char *var)
{
	for (int i = 0; i < numberOfVariables; i++)
	{
		Variable currentVariable = VARIABLES[i];

		if (!strcmp(currentVariable.name, var))
		{
			if (!strcmp(type(currentVariable.value), "String"))
			{
				return convertValueToString(currentVariable.value);
			}

		}
	}

	if (numberable(var))
	{
		return strdup(var);
	}

	if (!strcmp(type(var), "String"))
	{
		return convertValueToString(var);
	}

	if (!strcmp(type(var), "Null"))
	{
		return strdup(var);
	}

	if (!strcmp(type(var), "Bool"))
	{
		return strdup(var);
	}

	return strdup("");
}
