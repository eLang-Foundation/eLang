/// \param errorType The type of the error
/// \param error The error message
/// \param line The line on which the error occurred
/// \param i The line number
/// \param filename The name of the file, during the execution of which an error occurred
/// \author Bekhruz Niyazov
void raiseError(char *errorType, char *error, char *line, int i, char *filename)
{
	if (EXIT_WHEN_ERROR && strcmp(errorType, WARN) != 0) freeAll();
	// if the incorrect line of code was given
	if (line != NULL)
	{
		printf("File \"%s\"", filename);
		printf(", line %i\n", i);
		printf("    %s\n", trim(line));
	}
	// printing the error
	printf("%s: %s\n", errorType, error);
	// exiting the program
	if (EXIT_WHEN_ERROR && strcmp(errorType, WARN) != 0) exit(EXIT_FAILURE);
}
