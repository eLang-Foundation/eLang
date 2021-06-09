// this function checks if the given value can be converted to a number
bool numberable(char *value)
{
	size_t length = strlen(value);

	bool numberable = false;

	for (int i = 0; i < length; i++)
	{
		if (((int) value[i] >= 48 && (int) value[i] <= 57) || (int) value[i] == 46)
		{
			numberable = true;
		}
		else
		{
			numberable = false;
			break;
		}
	}
	
	return numberable;
}
