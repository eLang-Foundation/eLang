// function for raising errors
void raiseError(char *errorType, char *error, char *line, int lineNumber, char *filename)
{
	// if the incorrect line of code was given
	if (line != NULL)
	{
		printf("File \"%s\"", filename);
		printf(", line %i\n", lineNumber);
		printf("    %s\n", line);
	}
	// printing the error
	printf("%s: %s\n", errorType, error);
	// exiting the program
	exit(EXIT_FAILURE);
}
