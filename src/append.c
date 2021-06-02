// this function appends the given character to the given string
char *appendChar(char *string, char chr)
{
	size_t length = strlen(string);
	char tmp[length + 2];
	strcpy(tmp, string);
	tmp[length++] = chr;
	tmp[length++] = '\0';
	string = realloc(string, length);
	strcpy(string, tmp);
	return string;
}

// this function appends the given string to the given string
char *appendString(char *string, char *string2)
{
	size_t length = strlen(string);
	size_t length2 = strlen(string2);
	char tmp[length + length2 + 1];
	strcpy(tmp, string);
	for (int i = 0; i < length2; i++)
	{
		tmp[length++] = string2[i];
	}
	tmp[length++] = '\0';
	string = realloc(string, length);
	strcpy(string, tmp);
	return string;
}

