// this function checks if the given value can be converted to a number
bool numberable(char *value)
{
	return match(value, "[\\d\\.-]+");
}
