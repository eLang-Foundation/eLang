// an array of arguments will be stored in this variable
strArray getArguments(char *arguments)
{
    int length = count(',', arguments) + 1;
    char **args = malloc(length * sizeof(char *));

    int argCounter = 0;
    int charCounter = 0;

    char *argument;
    argument = malloc(0);

    // the following code splits the arguments string into separate arguments and adds them to the args array
    for (int i = 0, l = (int) strlen(arguments); i < l; i++)
    {
        if (arguments[i] != ',')
        {
            char tmp[charCounter + 2];
            strcpy(tmp, argument);
            tmp[charCounter++] = arguments[i];
            argument = realloc(argument, charCounter);
            strcpy(argument, tmp);
        }

        if ((!insideQuotes(i + 1, arguments) && arguments[i + 1] == ',') || (i == l - 1))
        {
            args[argCounter++] = strdup(trim(argument));
            charCounter = 0;
            free(argument);
            argument = malloc(0);
        }
    }

    free(argument);

    strArray array;
    array.array = args;
    array.allocated = true;
    array.length = length; 

    return array;
}
