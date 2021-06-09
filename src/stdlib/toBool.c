// this function converts the given value to a boolen
char *toBool(char *value)
{
	if (!strcmp(type(value), "bool"))
	{
		return value;
	}

	if (!strcmp(value, "0") || !strcmp(value, "undefined") || !strcmp(value, "null"))
	{
		return "false";
	}

	if (numberable(value) || toString(value, 1))
		return "true";

	return "false";
}
