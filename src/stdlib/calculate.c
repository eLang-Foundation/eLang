// this function calculates the given expression
double calculate(char *expression)
{
	char *tmp1 = get(expression, "([\\w\\W]+?)[\\+\\-\\*\\/]+");
	char *operator = get(expression, "[\\w\\W]+?([\\+\\-\\*\\/]+)");
	char *tmp2 = get(expression, "[\\+\\-\\*\\/]+([\\w\\W]+)");

	double number1 = toNumber(getValue(trim(tmp1)));
	double number2 = toNumber(getValue(trim(tmp2)));

	free(tmp1);
	free(tmp2);

	if (!strcmp(operator, "+"))
	{
		free(operator);
		return number1 + number2;
	}

	if (!strcmp(operator, "-"))
	{
		free(operator);
		return number1 - number2;
	}

	if (!strcmp(operator, "*"))
	{
		free(operator);
		return number1 * number2;
	}

	if (!strcmp(operator, "/"))
	{
		free(operator);
		return number1 / number2;
	}

	return 0;
}
