/// \param line The current line of code
/// \param after The code that follows the current line (including the current line)
/// \param elseStatement Whether the following line is an else statement or not
/// \author Bekhruz Niyazov
void ifStatement(char *line, char *after, bool elifStatement, bool elseStatement)
{
	char *expression = trim(get(line, "if\\s+([\\w\\W]+)\\s*\\{"));
	char *code = getContents(after, '{', '}');
	char *result = evaluate(expression, false, true);

	bool skipNext = false;

	if ((elseStatement && lastIfStatement == 1) || (!elseStatement && !strcmp(result, "false"))) skipNext = true;

	if (skipNext)
	{
		// checking if the next line of code is inside an if statement
		ignore = false;
		for (int i = 0, l = (int) strlen(code); i < l; i++)
		{
			if (code[i] == '\n' || code[i] == NEW_LINE_SEPARATOR)
			{
				ignore = true;
				break;
			}
		}
		if (!elifStatement) lastIfStatement = 0;
		IF_STATEMENT = true;
	}
	else
	{
		lastIfStatement = 1;
		IF_STATEMENT = false;
	}

	free(expression);
	free(code);
	free(result);
}
