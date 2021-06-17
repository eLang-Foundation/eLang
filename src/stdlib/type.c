// this function returns the type of the given value
char *type(char *value)
{
	int index = strlen(value) - 1;

	if ((value[0] == '"' && value[index] == '"') ||
		(value[0] == '\'' && value[index] == '\'') ||
		(value[0] == '`' && value[index] == '`'))
	{
		return "String";
	}

	if (numberable(value))
	{
		return "Number";
	}

	if (!strcmp(value, "true") || !strcmp(value, "false") || match(value, "[\\w\\W]+[<>=]+[\\w\\W]+"))
	{
		return "Bool";
	}	

	for (int i = 0; i < numberOfeLangFunctions; i++)
	{
		if (!strcmp(value, ELANG_FUNCTIONS[i]))
		{
			return "Function";
		}
	}

	for (int i = 0; i < numberOfFunctions; i++)
	{
		if (!strcmp(value, FUNCTIONS[i].name))
		{
			return "Function";
		}
	}

	if (!strcmp(value, "Null"))
	{
		return "Null";
	}

	return "Undefined";
}
