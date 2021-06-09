// this function extracts code from given string after (and including) line at the given index
char *getAfter(strArray lines, int index)
{
	int numberOfLines = lines.length;
	char *after = malloc(1);
	strcpy(after, "");
	for (ui j = index; j < numberOfLines; j++)
	{
		if (strcmp(lines.array[j], ""))
		{
			char *currentLine = strdup(lines.array[j]);
			after = appendString(after, currentLine);
			after = appendChar(after, '\n');
			free(currentLine);
		}
	}
	return after;
}
