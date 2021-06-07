// this function extracts code from given string after (and including) line at the given index
char *getAfter(char *code, strArray lines, int index, int numberOfLines)
{
	char *after = malloc(1);
	strcpy(after, "");
	for (ui j = index; j < numberOfLines; j++)
	{
		if (strcmp(lines.array[j], ""))
		{
			char *currentLine = strdup(lines.array[j]);
			after = appendString(after, currentLine);
			after = appendChar(after, '\n');
			checkClosed(j, code);
			free(currentLine);
		}
	}
	return strdup(after);
}
