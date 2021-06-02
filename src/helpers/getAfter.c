// this function extracts code from given string after (and including) line at the given index
char *getAfter(char *code, str lines[], int index, int numberOfLines)
{
	char *after = malloc(1);
	strcpy(after, "");
	for (ui j = index; j < numberOfLines; j++)
	{
		char *currentLine = strdup(lines[j].value);
		after = appendString(after, currentLine);
		after = appendChar(after, '\n');
		checkClosed(j, code);
		free(currentLine);
	}
	return strdup(after);
}
