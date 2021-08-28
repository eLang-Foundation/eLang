/// \param string The string index from which needs to be found
/// \param chr The character, index of which needs to be found inside the string
/// \return The index of the character (if found); else -1
/// \author Bekhruz Niyazov
int getIndex(const char *string, char chr)
{
	int counter = -1;
	int length = (int) strlen(string);
	for (; counter < length && string[counter] != chr; counter++);
	return counter;
}
