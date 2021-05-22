// this function removes whitespace around the string
char *trim(char *string)
{
	size_t size;
	char *end;

	size = strlen(string);

	if (!size)
		return string;

	end = string + size - 1;
	while (end >= string && *end == ' ')
		end--;
	*(end + 1) = '\0';

	while (*string && *string == ' ')
		string++;

	return string;
}