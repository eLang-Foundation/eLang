/*
 * eLang 1.0.0 C
 *
 * This is the first version of eLang written in C and C++
 *
 */

#include "headers.h"

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
		printf("eLang 0.1\n");
		return 0;
	}

	if (!strcmp(FILENAME, "--logo"))
	{
		printf("%s", logo);
		return 0;
	}

	setup();

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

	int wait = 0;
	// executing each line of code
	for (ui i = 0; i < LINES.length; i++)
	{
		char *line = LINES.array[i];

		if (!wait) ignore = false;
		// checking if the following code is inside a function or an if statement or a loop
		for (int j = 0, l = (int) strlen(line); j < l; j++)
		{
			// if the character represents the start of a code block,
			// and it is not a part of a string
			if (!insideQuotes(j, line))
			{
				if (line[j] == '{')
				{
					wait++;
				}
				else if (line[j] == '}')
				{
					if (wait)
						wait--;
					else
						ignore = false;
				}
			}
		}

		// getting an array of lines that are after the current line
		char *after = getAfter(LINES, (int) i);

		// checking for syntax errors
		checkClosed(i, CONTENTS);

		lineNumber = (int) i + 1;

		execute(trim(line), after, lineNumber);

		free(after);
		free(LINES.array[i]);
	}

	// freeing the allocated memory
	free(CONTENTS);
	free(LINES.array);

	freeAll();

	return 0;
}
