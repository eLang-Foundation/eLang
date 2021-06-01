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
