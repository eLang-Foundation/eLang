/// \param chr A character the number of occurrences of which needs to be counted
/// \param contents A string in which the number of chars will be counted
/// \return A number of occurrences of chr in contents
int count(char chr, char *contents)
{
	int counter = 0;
	for (int i = 0, l = (int) strlen(contents); i < l; i++)
	{
		if (contents[i] == chr)
		{
			if (!insideQuotes(i, contents))
				counter++;
		}
	}

	return counter;
}
