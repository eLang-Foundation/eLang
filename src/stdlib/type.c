// this function returns the type of the given value
char *type(char *value)
{
	int index = strlen(value) - 1;
	if ((value[0] == '"' && value[index] == '"') ||
		(value[0] == '\'' && value[index] == '\'') ||
		(value[0] == '`' && value[index] == '`'))
	{
		return "string";
	}
	return "undefined";
}
