// function for raising errors
void raiseError(char *errorType, char *error, char *line, int lineNumber, char *filename)
{
	if (EXIT_WHEN_ERROR && strcmp(errorType, WARN)) freeAll();
	// if the incorrect line of code was given
	if (line != NULL)
	{
		printf("File \"%s\"", filename);
		printf(", line %i\n", lineNumber);
		printf("    %s\n", trim(line));
	}
	// printing the error
	printf("%s: %s\n", errorType, error);
	// exiting the program
	if (EXIT_WHEN_ERROR && strcmp(errorType, WARN)) exit(EXIT_FAILURE);
}
