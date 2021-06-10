// this function evaluates the given expression
char *evaluate(char *expression)
{
	if (match(expression, "[\\w\\W]+?[<>=]+[\\w\\W]+?"))
	{
		return strdup(toBool(expression));
	}

	if (match(expression, "[\\w\\W]+?[\\+\\-\\*\\/]+[\\w\\W]+?"))
	{
		double result = calculate(expression);

		char returnString[100];

		sprintf(returnString, "%f", result);

		return strdup(returnString);
	}

	return strdup("");

}
