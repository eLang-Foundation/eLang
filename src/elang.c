/*
 * eLang 0.0.9 C
 *
 * This is the first version of eLang written in C and C++
 *
 */

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// C++ functions
extern char *get(char *, char *);
extern bool match(char *, char *);

// helper files
#include "helpers/variables.h"
#include "helpers/freeAll.c"
#include "helpers/raiseError.c"
#include "helpers/insideQuotes.c"
#include "helpers/count.c"
#include "helpers/checkClosed.c"
#include "helpers/trim.c"
#include "helpers/getContents.c"
#include "helpers/getIndex.c"
#include "helpers/append.c"
#include "helpers/getArguments.c"
#include "helpers/replace.c"
#include "helpers/getAfter.c"
#include "helpers/splitIntoLines.c"
#include "helpers/convertValueToString.c"
#include "helpers/getValue.c"

// eLang functions
#include "stdlib/numberable.c"
#include "stdlib/type.c"
#include "stdlib/toString.c"
#include "stdlib/toBool.c"
#include "stdlib/print.c"

// the execute function
#include "helpers/execute.c"

int main(int argc, char *argv[])
{
	// if the number of arguments is 2
	if (argc == 2)
		FILENAME = argv[1];
	else
	{
		printf("Usage: elang filename.elang\n");
		return 1;
	}

	// if user wants to get the version of eLang
	if (!strcmp(FILENAME, "--version"))
	{
		printf("eLang 0.0.9 C\n");
		return 0;
	}

	// if file was not successfully opened
	if (access(FILENAME, F_OK) != 0)
	{
		// creating a string that will be printed in a console
		char error[] = "Unable to open \"";
		strcat(error, FILENAME);
		strcat(error, "\"");
		// raising the error
		raiseError("eLang", error, NULL, 0, FILENAME);
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
	LINES = splitIntoLines(CONTENTS);

	// executing each line of code
	for (ui i = 0; i < LINES.length; i++)
	{
		char *line = strdup(LINES.array[i]);
		int wait = 0;

		// checking if the following code is inside of a function or an if statement or a loop
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

		// getting an array of lines that are after the current line
		char *after = getAfter(LINES, i);

		// checking for syntax errors
		checkClosed(i, after);

		execute(trim(line), after, i + 1);

		free(after);
		free(line);
		free(LINES.array[i]);
	}

	// freeing the allocated memory
	free(CONTENTS);
	free(LINES.array);

	freeAll();

	return 0;
}
