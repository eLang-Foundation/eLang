/// \param string The string which will be processed
/// \param openCharacter The character that represents the start of the contents
/// \param closeCharacter The character that represents the end of the contents
/// \return The contents got from the string
/// \author Bekhruz Niyazov
char *getContents(char *string, char openCharacter, char closeCharacter)
{
	char returnString[strlen(string)];
	int counter = 0;

	bool start = false;
	int charCounter = 0;

	for (int i = 0, l = (int) strlen(string); i < l; i++)
	{
		if (start)
			returnString[counter++] = string[i];
		if (string[i] == openCharacter)
		{
			charCounter++;
			start = true;
		}
		if (string[i + 1] == closeCharacter && start)
		{
			charCounter--;
		}
		if (charCounter == 0 && start)
		{
			returnString[counter] = '\0';
			return strdup(returnString);
		}
	}

	return strdup("");
}
