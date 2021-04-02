/*
 * eLang 0.0.9 C
 *
 * This is the first version of eLang written in C
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// function prototypes
void raiseError(char *errorType, char *error, char *line, int lineNumber);
bool insideQuotes(int index, const char *line);
void checkClosed(unsigned int number);
int count(char chr);
bool contains(char *string, char chr);

// global variables
char *filename;
char *contents;
char *lines[] = {};
char *elangFunctions[] = {"print"};

// structs
typedef struct {
	char *arguments;
	char *body;
} Function;

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
		return 0;
	}

	// if user wants to get the version of eLang
	if (!strcmp(filename, "--version"))
	{
		printf("eLang 0.0.9 (C)\n");
		return 1;
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
	size_t length = ftell(file);

	// moving the pointer back to the start of the file
	fseek(file, 0L, SEEK_SET);

	// storing the contents of the file in a contents array
	contents = malloc(length);

	// getting the contents
	if (contents)
		fread(contents, 1, length, file);

	// done with the contents
	fclose(file);

	char *contentsCopy = malloc((length * sizeof(char)) + 1);
	strncpy(contentsCopy, contents, length);

	// splitting the code into lines
	char *token = strtok(contentsCopy, "\n");
	unsigned int numberOfLines = 0;
	while (token != NULL)
	{
		lines[numberOfLines++] = token;
		token = strtok(NULL, "\n");
	}

	checkClosed(numberOfLines);

	// freeing the allocated memory
	free(contents);
	free(contentsCopy);

	return 1;
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
	exit(EXIT_FAILURE);
}

// this function checks if the character at a given index is not inside of a string
bool insideQuotes(int index, const char *line)
{
	// if there are no double or single quotes then they are closed
	bool closedSingleQuote = true;
	bool closedDoubleQuote = true;
	// cycling through each character in the given string until the given index
	for (int i = 0; i < index; i++)
	{
		// if the last character before the current character is not slash
		if (line[i-1] != '\\')
		{
			// if character is equal to " and it is not inside of a string
			if (line[i] == '"' && closedSingleQuote)
			{
				// the double quotes are opened if they were closed
				// and they are closed if they were opened
				closedDoubleQuote = !closedDoubleQuote;
			}
			// if the character is equal to ' and it is not inside of a string
			if (line[i] == '\'' && closedDoubleQuote)
			{
				// the single quotes are opened if they were closed
				// and they are closed if they were opened
				closedSingleQuote = !closedSingleQuote;
			}
		}
	}
	// if single and double quotes are closed
	if (closedSingleQuote && closedDoubleQuote)
		return false;
	return true;
}

// function that checks whether or not all parentheses, brackets and so forth are closed
void checkClosed(unsigned int number)
{
	char chars[] = {'"', '\'', '{', '(', '['};
	char *charName;
	int counter;
	for (int i = 0, l = sizeof(chars) / sizeof(chars[0]); i < l; i++)
	{
		char chr = chars[i];
		counter = count(chr);
		if (chr == '"')
			charName = "double quote";
		else if (chr == '\'')
			charName = "single quote";
		else if (chr == '{')
		{
			counter += count('}');
			charName = "curly bracket";
		}
		else if (chr == '(')
		{
			counter += count(')');
			charName = "parentheses";
		}
		else if (chr == '[')
		{
			counter += count(']');
			charName = "square bracket";
		}
		if (counter % 2 != 0 && counter != 0)
		{
			// displaying the error
			for (; number > 0;)
			{
				char *line = lines[--number];
				if (line)
				{
					if (strchr(line, chr) != NULL)
					{
						char str[] = "Unclosed ";
						strcat(str, charName);
						raiseError("SyntaxError", str, line, (int) number);
					}
				}
			}
		}
	}
}

int count(char chr)
{
	int counter = 0;
	for (int i = 0, l = (int) strlen(contents); i < l; i++)
	{
		if (contents[i] == chr)
		{
			if (!insideQuotes(i, contents))
				counter++;
			else
			{
				if (!insideQuotes(i+1, contents))
					counter++;
			}
		}
	}
	return counter;
}
