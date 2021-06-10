// this function calculates the given expression
double calculate(char *expression)
{
	size_t length = strlen(expression);

	char operators[count('+', expression) + count('-', expression) + count('*', expression) + count('/', expression)];

	int numberOfOperators = 0, numberOfNumbers = 0;

	double *numbers = calloc(1, sizeof(double));

	bool skipNext = false;

	for (int i = 0; i < length; i++)
	{
		switch (expression[i])
		{
			case '+':
				operators[numberOfOperators++] = '+';
				skipNext = false;
				break;
			case '-':
				operators[numberOfOperators++] = '-';
				skipNext = false;
				break;
			case '*':
				operators[numberOfOperators++] = '*';
				skipNext = false;
				break;
			case '/':
				operators[numberOfOperators++] = '/';
				skipNext = false;
				break;
			default:
				if (!skipNext)
				{
					char number[100];
					int j = 0;
					for (; j < length; j++)
					{
						if (expression[i + j] == '+' || expression[i + j] == '-' || expression[i + j] == '*' || expression[i + j] == '/')
							break;
						number[j] = expression[i + j];
					}
					number[j] = '\0';
					double num = toNumber(trim((char *) &number));
					numbers = realloc(numbers, ++numberOfNumbers * sizeof(double));
					numbers[numberOfNumbers - 1] = num;
					skipNext = true;
				}
				break;
		}
	}

	double returnValue = 0;

	for (int i = 0; i < numberOfOperators; i++)
	{
		switch (operators[i])
		{
			case '+':
				returnValue += numbers[i ? i + 1 : 0] + numbers[i ? i + 2 : 1];
				break;
			case '-':
				returnValue += numbers[i ? i + 1 : 0] - numbers[i ? i + 2 : 1];
				break;
			case '*':
				returnValue += numbers[i ? i + 1 : 0] * numbers[i ? i + 2 : 1];
				break;
			case '/':
				returnValue += numbers[i ? i + 1 : 0] / numbers[i ? i + 2 : 1];
				break;
		}
	}

	free(numbers);

	return returnValue;
}
