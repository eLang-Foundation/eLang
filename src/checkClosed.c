// function that checks whether or not all parentheses, brackets and so forth are closed
void checkClosed(unsigned int number, char *contents, char *lines[], char *filename)
{
	char chars[] = { '"', '\'', '{', '(', '[' };
	char *charName;
	int counter;
	for (int i = 0, l = sizeof(chars) / sizeof(chars[0]); i < l; i++)
	{
		char chr = chars[i];
		counter = count(chr, contents);
		if (chr == '"')
			charName = "double quote";
		else if (chr == '\'')
			charName = "single quote";
		else if (chr == '{')
		{
			counter += count('}', contents);
			charName = "curly bracket";
		}
		else if (chr == '(')
		{
			counter += count(')', contents);
			charName = "parentheses";
		}
		else if (chr == '[')
		{
			counter += count(']', contents);
			charName = "square bracket";
		}
		// if number is not even
		if (counter % 2 != 0 && counter != 0)
		{
			// displaying the error
			for (; number > 0;)
			{
				// getting the line
				char *line = lines[--number];
				if (line)
				{
					// displaying the error
					if (strchr(line, chr) != NULL)
					{
						char str[] = "Unclosed ";
						strcat(str, charName);
						raiseError("SyntaxError", str, line, (int) number, filename);
					}
				}
			}
		}
	}
}
