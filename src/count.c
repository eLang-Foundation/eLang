// this function counts the number of the occurrences of the given character in the given string
// (excludes the ones that are inside of quotes)
int count(char chr, char *contents)
{
	int counter = 0;
	for (int i = 0, l = (int) strlen(contents); i < l; i++)
	{
		if (contents[i] == chr)
		{
			if (!insideQuotes(i, contents))
				counter++;
			else
			{
				if (!insideQuotes(i + 1, contents))
					counter++;
			}
		}
	}
	return counter;
}
