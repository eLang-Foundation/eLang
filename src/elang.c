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
#include <regex.h>

// function prototypes
void raiseError(char *errorType, char *error, char *line, int lineNumber);

bool insideQuotes(int index, const char *line);

void checkClosed(unsigned int number);

int count(char chr);

void execute(char *line, char *after);

int match(const char *string, const char *pattern);

char *get(const char *string, const char *pattern);

int getIndex(const char *string, char chr);

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
		raiseError("eLang", str, NULL, 0);
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
	checkClosed(numberOfLines);

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

		execute(line, after);

	}

	// freeing the allocated memory
	free(CONTENTS);
	free(contentsCopy);

	exit(EXIT_SUCCESS);
}

// function for raising errors
void raiseError(char *errorType, char *error, char *line, int lineNumber)
{
	// if the incorrect line of code was given
	if (line != NULL)
	{
		printf("File \"%s\"", FILENAME);
		printf(", line %i\n", lineNumber);
		printf("    %s\n\n", line);
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
		if (line[i - 1] != '\\')
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
	char chars[] = { '"', '\'', '{', '(', '[' };
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
		// if number is not even
		if (counter % 2 != 0 && counter != 0)
		{
			// displaying the error
			for (; number > 0;)
			{
				// getting the line
				char *line = LINES[--number];
				if (line)
				{
					// displaying the error
					if (strchr(line, chr) != NULL)
					{
						char str[] = "Unclosed ";
						strcat(str, charName);
						raiseError("SyntaxError", str, line, (int)number);
					}
				}
			}
		}
	}
}

// this function counts the number of the occurrences of the given character in the given string
// (excludes the ones that are inside of quotes)
int count(char chr)
{
	int counter = 0;
	for (int i = 0, l = (int)strlen(CONTENTS); i < l; i++)
	{
		if (CONTENTS[i] == chr)
		{
			if (!insideQuotes(i, CONTENTS))
				counter++;
			else
			{
				if (!insideQuotes(i + 1, CONTENTS))
					counter++;
			}
		}
	}
	return counter;
}

// this function checks whether the given string matches the given regex pattern
int match(const char *string, const char *pattern)
{
	regex_t re;
	if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0) return 0;
	int status = regexec(&re, string, 0, NULL, 0);
	regfree(&re);
	if (status != 0) return 0;
	return 1;
}

// this function returns the index of the first occurrence of the given character in the given string
int getIndex(const char *string, char chr)
{
	int counter = 0;
	while (string[counter++] != chr);
	return counter;
}

// this function returns the string found using given regex pattern
char *get(const char *string, const char *pattern)
{
	int sizeBefore = 0;
	int sizeAfter = 0;
	bool done = false;
	bool wait = false;
	for (int i = 0, l = (int) strlen(pattern); i < l; i++)
	{
		if (pattern[i] == '[' && pattern[i + 1] == ']')
			done = true;
		else
		{
			if (done)
				wait = true;
			if (wait)
				sizeAfter++;
			else
				sizeBefore++;
		}
	}

	char before[sizeBefore];
	char after[sizeAfter];
	for (int i = 0, l = (int) strlen(pattern); i < l;)
	{
		if (i < sizeBefore)
		{
			before[i] = pattern[i];
			i++;
		}
		else
		{
			before[sizeBefore] = '\0';
			for (int j = i + 2; j < l; j++)
			{
				if (j - sizeBefore > 1)
				{
					printf("here\n");
					after[j - i - 2] = pattern[j];
				}
			}
			break;
		}
	}
	after[sizeAfter] = '\0';

	printf("%s | %s\n", before, after);

	return strdup("");
}

// this function executed the given code
void execute(char *line, char *after)
{
	int counter = 0;
	char *token = strtok(line, " ");

	// getting the size of the array
	while (token != NULL)
	{
		counter++;
		token = strtok(NULL, " ");
	}

	// creating an array of words
	char *words[counter];
	token = strtok(line, " ");
	counter = 0;

	// filling in the array of words
	while (token != NULL)
	{
		words[counter++] = strdup(token);
		token = strtok(NULL, " ");
	}

	char *functionKeyword = "function";

	if (counter)
	{
		if (!ignore)
		{
			if (!strcmp(words[0], functionKeyword))
			{
				// getting the name of the function
				char *returnValue = get(after, "[{][][}]");
				printf("%s\n", returnValue);
				free(returnValue);
			}
		}
	}

	for (int i = 0; i < counter; i++)
	{
		free(words[i]);
	}

}
