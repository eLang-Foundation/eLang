#include <stdio.h>
#include <string.h>

// this function returns the string found using given regex pattern
char *get(const char *string, const char *pattern)
{
	// getting the size of the string before and after the pattern inside of []
	int sizeBefore = 1, sizeAfter = 1;
	bool doneBefore = false, startAfter = false;
	for (int i = 0, l = (int) strlen(pattern); i < l; i++)
	{
		if (pattern[i] == '[')
			doneBefore = true;
		else if (pattern[i] == ']')
			startAfter = true;
		if (!doneBefore)
			sizeBefore++;
		else if (startAfter)
			sizeAfter++;
	}

	// getting the patterns
	char before[sizeBefore], after[sizeAfter];
	int counter = 0;
	for (int i = 0, l = (int) strlen(pattern); i < l; i++)
	{
		if (i < sizeBefore - 1)
			before[i] = pattern[i];
		else
		{
			before[i] = '\0';
			if (i > l - sizeAfter + 1)
			{
				after[counter++] = pattern[i];
			}
		}
	}

	printf("Before:%s\nAfter: %s\n", before, after);
	printf("here");

	char returnString[strlen(string)];
	counter = 0;
	for (int i = 0, l = (int) strlen(string); i < l; i++)
	{
//		if (regex_matches((regex *)&before, (char *) &returnString, (capture_group **)"[\\w\\W]*") != 0)
//		{
//			returnString[counter++] = string[i];
//			printf("%c", string[i]);
//		}
	}

	printf("\n");

	return strdup(returnString);
}
