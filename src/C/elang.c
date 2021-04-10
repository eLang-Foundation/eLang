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
void execute(char *line, char *after);

// global variables
char *filename;
char *contents;
char *lines[] = {};
char *elangFunctions[] = {"print"};

bool ignore = false;

// structs
typedef struct {
	char *name;
	char *arguments;
	char *body;
} Function;

typedef struct {
	char *name;
	char *value;
} Variable;

Function functions[] = {};
Variable variables[] = {};

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
		printf("eLang 0.0.9 C\n");
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

	char *contentsCopy = malloc(strlen(contents) + 1);
	strcpy(contentsCopy, contents);

	// splitting the code into lines
	char *token = strtok(contentsCopy, "\n");
	unsigned int numberOfLines = 0;
	while (token != NULL)
	{
		lines[numberOfLines++] = token;
		token = strtok(NULL, "\n");
	}

	// checking for syntax errors
	checkClosed(numberOfLines);

	for (int i = 0; i < numberOfLines; i++)
	{
		char *line = lines[i];
		int wait = 0;

		// checking if the following code is inside of a function
		if (ignore)
		{
			for (int j = 0; j < strlen(line); j++)
			{
				// if the character represents the start of a code block
				// and it is not a part of a string
				if (line[j] == '{' && !insideQuotes(j, line))
					wait++;
				if (line[j] == '}' && !insideQuotes(j, line))
				{
					if (wait)
						wait--;
					else
						ignore = false;
				}
			}
		}

		// creating an array of lines that are after the current line
		char *after;
		char *afterArray[] = {};

		int counter = 0;

		for (int j = i; j < numberOfLines; j++)
		{
			afterArray[counter] = malloc(strlen(lines[j]) + 1);
			strcpy(afterArray[counter++], lines[j]);
		}

		for (int j = 0; j < counter; j++)
		{
			char *string = afterArray[j];
			char tmp[(j == 0 ? 0 : strlen(after)) + strlen(string) + 10];
			strcpy(tmp, j == 0 ? "" : after);
			strcat(tmp, string);
			strcat(tmp, "\n");
			after = (char *) tmp;
			free(string);
		}

		execute(line, after);
	}

	// freeing the allocated memory
	free(contents);
	free(contentsCopy);

	exit(EXIT_SUCCESS);
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
	printf("\n%s: %s\n", errorType, error);
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

// this function counts the number of the occurrences of the given character in the even string
// (excludes the ones that are inside of quotes)
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

void execute(char *line, char *after)
{
	char *words[] = {};

	char *lineCopy = malloc(strlen(line) + 1);
	strcpy(lineCopy, line);

	int counter = 0;

	char *token = strtok(lineCopy, " ");
	while (token != NULL)
	{
		words[counter++] = token;
		token = strtok(NULL, " ");
	}

	free(lineCopy);

	for (int i = 0; i < counter; i++)
	{
		printf("%s\n", words[i]);
	}

}
