/// \param value The value that needs to be checked
/// \return true if the value can be converted to number; else false
/// \author Bekhruz Niyazov
bool numberable(char *value)
{
	return match(value, "[\\d\\.-]+") || !strcmp(value, "true") || !strcmp(value, "false");
}
