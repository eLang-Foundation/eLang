// this function does the if statement stuff
void ifStatement(char *line, char *after)
{
	char *expression = trim(get(line, "if\\s+([\\w\\W]+)\\s*\\{"));

	char *code = getContents(after, '{', '}');

	char *result = evaluate(expression);

	if (!strcmp(toBool(result), "false"))
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
	}

	free(expression);
	free(code);
	free(result);
}
