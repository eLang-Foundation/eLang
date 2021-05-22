// this function gets text in between the given characters in the given string
char *getContents(char *string, char openCharacter, char closeCharacter)
{
	char returnString[strlen(string)];
	int counter = 0;

	bool start = false;
	int charCounter = 0;

	for (int i = 0, l = (int) strlen(string); i < l; i++)
	{
		if (start)
		{
			returnString[counter++] = string[i];
		}
		if (string[i] == openCharacter)
		{
			start = true;
			charCounter++;
		}
		else if (string[i + 1] == closeCharacter)
		{
			charCounter--;
			if (charCounter == 0)
			{
				returnString[counter] = '\0';
				return strdup(returnString);
			}
		}
	}

	return strdup("");
}
