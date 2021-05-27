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
#include "variables.h"
#include "raiseError.c"
#include "insideQuotes.c"
#include "count.c"
#include "checkClosed.c"
#include "trim.c"
#include "getContents.c"
#include "execute.c"

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
		char str[] = "Unable to open \"";
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

	// storing the contents of the file in a CONTENTS array
	CONTENTS = malloc(length + 1);

	// getting the contents
	if (CONTENTS)
		fread(CONTENTS, 1, length, file);

	// done with the contents
	fclose(file);

	// splitting the code into lines
	unsigned int numberOfLines = 0;
	unsigned int charCount = 0;
	char ln[] = "";
	for (unsigned int i = 0, l = (int) strlen(CONTENTS); i < l; i++)
	{
		if (CONTENTS[i] != '\n')
		{
			ln[charCount++] = CONTENTS[i];
		}
		else
		{
			ln[charCount] = '\0';
			charCount = 0;
			LINES[numberOfLines++] = strdup(ln);
		}
	}

	int functionCountVariable = 0;
	int *functionCount = &functionCountVariable;

	// executing each line of code
	for (unsigned int i = 0; i < numberOfLines; i++)
	{
		char *line = LINES[i];
		int wait = 0;

		// checking if the following code is inside of a function
		if (ignore)
		{
			for (int j = 0, l = (int) strlen(line); j < l; j++)
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
		char after[] = " ";
		for (unsigned int j = i; j < numberOfLines; j++)
		{
			strcat(after, LINES[j]);
			strcat(after, "\n");
			checkClosed(j, CONTENTS);
		}

		execute(trim(line), after, functionCount);
		puts(LINES[i]);
		free(LINES[i]);
	}

	// freeing the allocated memory
	free(CONTENTS);

	exit(EXIT_SUCCESS);
}
