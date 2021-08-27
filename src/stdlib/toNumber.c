/// \param string The string that needs to be converted
/// \return String converted to double
/// \author Bekhruz Niyazov
double toNumber(char *string)
{
	if (!strcmp(string, "true"))
		return 1;

	if (!strcmp(string, "false"))
		return 0;

    if (numberable(trim(string)))
	{
		double number;
		char *ptr;
		number = strtod(trim(string), &ptr);
		return number;
	}

	char error[] = "Couldn't convert \"";
	strcat(error, string);
	strcat(error, "\" to a Number");
	raiseError(INV, error, LINES.array[lineNumber - 1], lineNumber, FILENAME);
	
	return 0;
}
