// this function does the if statement stuff
void ifStatement(char *line, char *after, bool elseStatement)
{
	char *expression = trim(get(line, "if\\s+([\\w\\W]+)\\s*\\{"));

	char *code = getContents(after, '{', '}');

	char *result = evaluate(expression, true);

	bool skipNext = false;

	if (elseStatement && lastIfStatement == 0) skipNext = false;
	if (elseStatement && lastIfStatement == 1) skipNext = true;
	if (!elseStatement && !strcmp(toBool(result), "false")) skipNext = true;

	if (skipNext)
	{
		// checking if the next line of code is inside of an if statement
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
