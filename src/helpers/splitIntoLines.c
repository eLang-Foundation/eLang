/// \param code The code which needs to be split
/// \return An array of strings, each representing a line of code
/// \author Bekhruz Niyazov
strArray splitIntoLines(char *code)
{
	strArray lines;
	char **array = calloc(count('\n', code) + count(NEW_LINE_SEPARATOR, code), sizeof(char *));

	int numberOfLines = 0;
	char *ln = strdup("");
	for (int i = 0, l = (int) strlen(code); i < l; i++)
	{
		if (code[i] != '\n' && code[i] != NEW_LINE_SEPARATOR)
		{
			ln = appendChar(ln, code[i]);
		}

		if (code[i] == '\n' || code[i] == NEW_LINE_SEPARATOR || i == l - 1)
		{
			array[numberOfLines++] = strdup(ln);
			free(ln);
			ln = strdup("");
		}
	}
	free(ln);

	lines.array = array;
	lines.length = numberOfLines;

	return lines;
}
