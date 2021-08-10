/// \param lines An array of lines of type strArray
/// \param index An index, starting from which lines should be appended to after
/// \return String, containing all lines of strArray lines starting from given index
/// \attention Return value should be freed after usage
/// \author Bekhruz Niyazov
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
