// this function converts the given value to string (removes the quotes on either end)
char *convertValueToString(char *value)
{
    char *string = malloc(1);
    strcpy(string, "");
    for (int h = 1, l = strlen(value); h < l - 1; h++)
    {
        string = appendChar(string, value[h]);
    }
    return string;
}
