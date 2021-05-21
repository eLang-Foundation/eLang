// this function removes the whitespace around the string
char *removeWhitespace(char *string)
{
	char *returnString = "";
	char *tmp = string;
	for (int i = 0, l = (int) strlen(tmp); i < l; i++)
	{
		if (tmp[i] == ' ' || tmp[i] == '\t' || tmp[i] == '\n')
		{
			returnString = &tmp[i + 1];
			tmp[i] = '\0';
		}
		else
			break;
	}
	for (int i = (int) strlen(tmp) - 1, l = 0; i >= l; i--)
	{
		if (tmp[i] == ' ' || tmp[i] == '\t' || tmp[i] == '\n')
		{
			tmp[i] = '\0';
		}
		else
			break;
	}
	return strdup(returnString);
}
