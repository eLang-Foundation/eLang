// this function extracts code from given string after (and including) line at the given index
char *getAfter(strArray lines, int index)
{
	ui numberOfLines = lines.length;
	char *after = strdup("");
	for (ui j = index; j < numberOfLines; j++)
	{
		char *currentLine = strdup(lines.array[j]);
		after = appendString(after, currentLine);
		after = appendChar(after, '\n');
		free(currentLine);
	}
	return after;
}
