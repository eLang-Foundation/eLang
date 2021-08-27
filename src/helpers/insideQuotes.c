/// \param index The index, character in the line at which should be checked
/// \param line The line that should be checked
/// \return true if the character at index is inside of quotes else false
/// \author Bekhruz Niyazov
bool insideQuotes(int index, const char *line)
{
	// if there are no double or single quotes then they are closed
	bool closedSingleQuote = true;
	bool closedDoubleQuote = true;
	// cycling through each character in the given string until the given index
	for (int i = 0; i < index; i++)
	{
		// if the last character before the current character is not slash
		if (line[i - 1] != '\\')
		{
			// if character is equal to " and it is not inside a string
			if (line[i] == '"' && closedSingleQuote)
			{
				// the double quotes are opened if they were closed,
				// and they are closed if they were opened
				closedDoubleQuote = !closedDoubleQuote;
			}
			// if the character is equal to ' and it is not inside a string
			if (line[i] == '\'' && closedDoubleQuote)
			{
				// the single quotes are opened if they were closed,
				// and they are closed if they were opened
				closedSingleQuote = !closedSingleQuote;
			}
		}
	}
	// if single and double quotes are closed
	if (closedSingleQuote && closedDoubleQuote)
		return false;
	return true;
}
