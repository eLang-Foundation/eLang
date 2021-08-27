/// \param string A string which needs to be converted to a boolean
/// \return "true" if the string represents "true"; else "false"
/// \author Bekhruz Niyazov

#define final free(operator);
#define check ? "true" : "false";

char *toBool(char *string)
{
	if (match(string, "\\d+"))
	{
		if (strcmp(string, "0") != 0)
		{
			return "true";
		}
		return "false";
	}

	if (!strcmp(string, "true") || !strcmp(string, "false"))
		return string;

	if (match(string, "[0\\.]+") || !strcmp(string, "undefined") || !strcmp(string, "null"))
		return "false";

	if (match(string, "[\\w\\W]+?[\\<\\>\\=\\-\\+\\|\\&]+[\\w\\W]+?"))
	{
		char *tmp1 = get(string, "([\\w\\W]+?)[\\<\\>\\=\\-\\+\\|\\&]+");
		char *operator = get(string, "[\\w\\W]+?([\\<\\>\\=\\-\\+\\|\\&]+)[\\w\\W]+");
		char *tmp2 = get(string, "[\\<\\>\\=\\-\\+\\|\\&]+([\\w\\W]+)");

		char *value1 = getValue(trim(tmp1));
		char *value2 = getValue(trim(tmp2));

		if (numberable(value1) && numberable(value2))
		{
			double number1 = toNumber(value1);
			double number2 = toNumber(value2);

			free(value1);
			free(value2);
			free(tmp1);
			free(tmp2);

			if (!strcmp(operator, "<"))
			{
				final
				return number1 < number2 check
			}

			else if (!strcmp(operator, ">"))
			{
				final
				return number1 > number2 check
			}

			else if (!strcmp(operator, ">="))
			{
				final
				return number1 >= number2 check
			}
			
			else if (!strcmp(operator, "<="))
			{
				final
				return number1 <= number2 check
			}

			else if (!strcmp(operator, "=="))
			{
				final
				return number1 == number2 check
			}

			else if (!strcmp(operator, "<-"))
			{
				final
				return number1 - 1 < number2 check
			}

			else if (!strcmp(operator, ">-"))
			{
				final
				return number1 - 1 > number2 check
			}

			else if (!strcmp(operator, "<+"))
			{
				final
				return number1 + 1 < number2 check
			}

			else if (!strcmp(operator, ">+"))
			{
				final
				return number1 + 1 > number2 check
			}

			else if (!strcmp(operator, "=-"))
			{
				final
				return number1 - 1 == number2 check
			}

			else if (!strcmp(operator, "=+"))
			{
				final
				return number1 + 1 == number2 check
			}

			else if (!strcmp(operator, "|"))
			{
				final
				return number1 || number2 check
			}

			else if (!strcmp(operator, "&"))
			{
				final
				return number1 && number2 check
			}

			else
			{
				char error[] = "Operator \"";
				strcat(error, operator);
				final
				strcat(error, "\" is not recognized");
				raiseError(INS, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
			}

		}
		else
		{
			if (strcmp(operator, "==") != 0)
			{
				char error[] = "Couldn't compare values ";
				strcat(error, value1);
				strcat(error, " and ");
				strcat(error, value2);
				strcat(error, " using the ");
				strcat(error, operator);
				strcat(error, " operator");
				free(value1);
				free(operator);
				free(value2);
				raiseError(INV, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
			}
		}
	}

	char *tmp = toString(string);
	if (strcmp(tmp, "") != 0)
	{
		free(tmp);
		return "true";
	}
	free(tmp);

	return "false";
}
