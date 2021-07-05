/// \param value A value that needs to be converted to string (e.g. "\"hello\"")
/// \return A value without quotes on each side (e.g. "\"hello\"" becomes "hello")
/// \author Bekhruz Niyazov
char *convertValueToString(char *value)
{
    char *string = malloc(1);
    strcpy(string, "");
    for (int h = 1, l = (int) strlen(value); h < l - 1; h++)
    {
        string = appendChar(string, value[h]);
    }
    return string;
}
