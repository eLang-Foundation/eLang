// this function evaluates the given expression
char *evaluate(char *expression, bool mathematicalExpression)
{

	// if a boolean expression
	if (match(expression, "[\\w\\W]+?[<>=]+[\\w\\W]+?"))
	{
		return strdup(toBool(expression));
	}

	if (mathematicalExpression)
	{
		if (match(expression, "[\\w\\W]+?[\\+\\-\\*\\/]+[\\w\\W]+?"))
		{
			double result = calculate(expression);

			char returnString[100];

			sprintf(returnString, "%f", result);

			return strdup(returnString);
		}
	}

	// if a function was called
	if (match(expression, "[\\w\\d_]+?\\([\\w\\W]*\\)"))
	{
		functionCall(expression, expression);
		return strdup(lastReturnValue);
	}

	return strdup(expression);

}
