// this function converts the given string to a number
double toNumber(char *string)
{
    if (numberable(string))
	{
		double returnValue = 0;

		size_t length = strlen(string);

		bool floatValue = false;

		if (count('.', string)) floatValue = true;

		if (floatValue)
		{
			char *parts[2];

			int index = 0;

			char *part = strtok(string, ".");
			while (part != NULL)
			{
				parts[index++] = strdup(part);
				part = strtok(NULL, ".");
			}

			for (int i = (int) strlen(parts[0]) - 1; i >= 0; i--)
			{
				returnValue += ((int) parts[0][i] - 48) * pow(10, i);
			}
			free(parts[0]);

			if (index > 1)
			{
				for (int i = 0, l = (int) strlen(parts[1]); i < l; i++)
				{
					returnValue += ((int) parts[1][i] - 48) / pow(10, i + 1);
				}
				free(parts[1]);
			}
		}

		else
		{
			for (int i = 0; i < length; i++)
			{
				int n = (int) string[i] - 48;
				if (n == 0) returnValue *= 10;
				else returnValue += n * (i > 1 ? pow(10, i) : 1);
			}
		}

		return returnValue;
	}

	char error[] = "Couldn't convert \"";
	strcat(error, string);
	strcat(error, "\" to a Number");
	raiseError(INV, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
	
	return 0;
}
