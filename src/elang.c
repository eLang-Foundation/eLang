/*
 * eLang 0.0.9 C
 *
 * This is the first version of eLang written in C and C++
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "raiseError.c"
#include "insideQuotes.c"
#include "count.c"
#include "checkClosed.c"
#include "execute.c"

// global variables
char *FILENAME;
char *CONTENTS;
char *LINES[] = {};
char *ELANG_FUNCTIONS[] = { "print" };

bool ignore = false;

// structs
typedef struct
{
	char *name;
	char *arguments;
	char *body;
} Function;

typedef struct
{
	char *name;
	char *value;
} Variable;

Function FUNCTIONS[] = {};
Variable VARIABLES[] = {};

// main function
int main(int argc, char *argv[])
{
	// if the number of arguments is 2
	if (argc == 2)
		FILENAME = argv[1];
	else
	{
		printf("Usage: elang filename.elang\n");
		return 0;
	}

	// if user wants to get the version of eLang
	if (!strcmp(FILENAME, "--version"))
	{
		printf("eLang 0.0.9 C\n");
		return 1;
	}

	// if file was not successfully opened
	if (access(FILENAME, F_OK) != 0)
	{
		// creating a string that will be printed in a console
		char str[] = "unable to open \"";
		strcat(str, FILENAME);
		strcat(str, "\"");
		// raising the error
		raiseError("eLang", str, NULL, 0, FILENAME);
	}

	// opening the file
	FILE *file = fopen(FILENAME, "r");

	// moving the pointer to the end of the file
	fseek(file, 0L, SEEK_END);

	// getting the length of the file
	size_t length = ftell(file);

	// moving the pointer back to the start of the file
	fseek(file, 0L, SEEK_SET);

	// storing the CONTENTS of the file in a CONTENTS array
	CONTENTS = malloc(length + 1);

	// getting the CONTENTS
	if (CONTENTS)
		fread(CONTENTS, 1, length, file);

	// done with the CONTENTS
	fclose(file);

	char *contentsCopy = malloc(length + 1);
	strcpy(contentsCopy, CONTENTS);

	// splitting the code into LINES
	char *token = strtok(contentsCopy, "\n");
	unsigned int numberOfLines = 0;
	while (token != NULL)
	{
		LINES[numberOfLines++] = token;
		token = strtok(NULL, "\n");
	}

	// checking for syntax errors
	checkClosed(numberOfLines, CONTENTS, LINES, FILENAME);

	for (int i = 0; i < numberOfLines; i++)
	{
		char *line = LINES[i];
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

		// creating an array of LINES that are after the current line
		char *after = "";
		char *afterArray[] = {};

		int counter = 0;

		for (int j = i; j < numberOfLines; j++)
			afterArray[counter++] = strdup(LINES[j]);

		for (int j = 0; j < counter; j++)
		{
			char *tmp = malloc(strlen(after) + strlen(afterArray[j]) + 1);
			strcpy(tmp, after);
			strcat(tmp, afterArray[j]);
			strcat(tmp, "\n");
			after = strdup(tmp);
			free(tmp);
		}

		execute(line, after, ignore);

	}

	// freeing the allocated memory
	free(CONTENTS);
	free(contentsCopy);

	exit(EXIT_SUCCESS);
}
