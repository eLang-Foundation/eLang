/// \param expression The expression to be evaluated
/// \param mathematicalExpression If the expression is an mathematical expression or not
/// \attention The return value should be freed after usage
/// \author Bekhruz Niyazov
char *evaluate(char *expression, bool mathematicalExpression, bool booleanExpression)
{
	// if a boolean expression
	if (match(expression, "[\\w\\W]+?[<>=\\|\\&]+[\\w\\W]+?") || (match(expression, "\\d+") && booleanExpression))
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
