// function that checks whether or not all parentheses, brackets and so forth are closed
void checkClosed(unsigned int number, char *code)
{
	char chars[] = {'"', '\'', '{', '(', '['};

	char error[32] = "Character \"";

	char *charName;
	int counter;
	for (int i = 0, l = sizeof(chars) / sizeof(chars[0]); i < l; i++)
	{
		char chr = chars[i];
		counter = count(chr, code);

		switch (chr)
		{
			default:
				strcat(error, &chr);
				strcat(error, "\" is not recognized");
				raiseError("eLang", error, NULL, 0, FILENAME);
				break;
			case '"':
				charName = "double quote";
				counter += count(chr, code);
				break;
			case '\'':
				charName = "single quote";
				counter += count(chr, code);
				break;
			case '{':
				charName = "curly bracket";
				counter += count('}', code);
				break;
			case '(':
				charName = "parentheses";
				counter += count(')', code);
				break;
			case '[':
				charName = "square bracket";
				counter += count(']', code);
				break;
		}
		// if number is not even
		if (counter % 2 != 0 && counter != 0)
		{
			// getting the line
			char *line = LINES.array[number];
			if (line)
			{
				// displaying the error
				if (strchr(line, chr) != NULL)
				{
					char str[] = "Unclosed ";
					strcat(str, charName);
					raiseError(INS, str, line, (int) number + 1, FILENAME);
				}
			}
		}
	}
}
