#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// function prototypes
void raiseError(char *errorType, char *error, char *line, int lineNumber);
int findIndexByKey(char *dict[8][2], char *key);
int findIndexByValue(char *dict[8][2], char *value);

// global variables
char *filename;
char contents[] = {};
char *lines[] = {};
char *syntax[][2] = {{"function", "function"}, {"start", "{"}, {"end", "}"},
                    {"arguments_start", ")"}, {"arguments_end", "("}};;
char *chars[][2] = {{"\"", "double quote"}, {"'", "single quote"},
                     {syntax[findIndexByKey(syntax, "start")][1], "curly bracket"},
                     {syntax[findIndexByKey(syntax, "end")][1], "close curly bracket"},
                     {syntax[findIndexByKey(syntax, "arguments_start")][1], "parentheses"},
                     {syntax[findIndexByKey(syntax, "arguments_end")][1], "close parentheses"},
                     {"[", "square brackets"}, {"]", "close square brackets"}};

// main function
int main(int argc, char *argv[])
{
	// if the number of arguments is 2
	if (argc == 2)
	{
		filename = argv[1];
	}
	else
	{
		printf("Usage: elang filename.elang\n");
		return 1;
	}

	// if user wants to get the version of eLang
	if (!strcmp(filename, "--version"))
	{
		printf("eLang 0.0.9 (C)\n");
		return 0;
	}

	// if file was not successfully opened
	if (access(filename, F_OK) != 0)
	{
		// creating a string that will be printed in a console
		char str[] = "unable to open \"";
		strcat(str, filename);
		strcat(str, "\"");
		// raising the error
		raiseError("eLang", str, NULL, 0);
	}

	// opening the file
	FILE *file = fopen(filename, "r");

	// moving the pointer to the end of the file
	fseek(file, 0L, SEEK_END);

	// getting the length of the file
	int length = ftell(file);

	// moving the pointer back to the start of the file
	fseek(file, 0L, SEEK_SET);

	char temp[length];

	// storing the contents of the file in a contents array
	while (fgets(temp, length, file))
	{
		strcat(contents, temp);
	}
	// done with the contents
	fclose(file);

	// creating a pointer that points to an allocated memory that stores the copy of the contents
	char *contentsPointer = malloc(length * sizeof(char));
	memcpy(contentsPointer, contents, length);

	// splitting the code into lines
	int counter = 0;
	char *token = strtok(contentsPointer, "\n");
	while (token != NULL)
	{
		lines[counter++] = token;
		token = strtok(NULL, "\n");
	}

	// freeing the allocated memory
	free(contentsPointer);

	return 0;
}

// function for raising errors
void raiseError(char *errorType, char *error, char *line, int lineNumber)
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
	exit(1);
}

// this function will return the index of the array that contains the given key
int findIndexByKey(char *dict[8][2], char *key)
{
	// cycling through each array in array
	for (int i = 0, l = sizeof(dict) * sizeof(dict[0]); i < l; i++)
	{
		// if the key in array is equal to given key
		if (!strcmp(key, dict[i][0]))
		{
			return i;
		}
	}
	return -1;
}

int findIndexByValue(char *dict[8][2], char *value)
{
	// cycling through each array in array
	for (int i = 0, l = sizeof(dict) * sizeof(dict[0]); i < l; i++)
	{
		// if the value in array is equal to given value
		if (!strcmp(value, dict[i][0]))
		{
			return i;
		}
	}
	return -1;
}
