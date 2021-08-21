/// \param line The current line of code
/// \param after The code that follows after the current line (including the current line)
/// \param elseStatement If the following line is an if statement or not
/// \author Bekhruz Niyazov
void ifStatement(char *line, char *after, bool elseStatement)
{
	char *expression = trim(get(line, "if\\s+([\\w\\W]+)\\s*\\{"));

	char *code = getContents(after, '{', '}');

	char *result = evaluate(expression, true);

	bool skipNext = false;

	if (elseStatement && lastIfStatement == 0) skipNext = false;
	else if ((elseStatement && lastIfStatement == 1) || (!elseStatement && !strcmp(result, "false"))) skipNext = true;

	if (skipNext)
	{
		// checking if the next line of code is inside an if statement
		ignore = false;
		for (int i = 0, l = (int) strlen(code); i < l; i++)
		{
			if (code[i] == '\n')
			{
				ignore = true;
				break;
			}
		}
		lastIfStatement = 0;
	}
	else
	{
		lastIfStatement = 1;
	}

	free(expression);
	free(code);
	free(result);
}
