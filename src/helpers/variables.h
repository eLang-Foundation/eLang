#define ui unsigned int

// structs
typedef struct
{
	char *value;
	bool allocated;
} str;

typedef struct
{
	char **array;
	bool allocated;
	int length;
} strArray;

typedef struct
{
	char *name;
	char **arguments;
	char *code;
	int argumentsNumber;
} Function;

typedef struct
{
	char *name;
	char *value;
} Variable;

// global variables
char *FILENAME;
char *CONTENTS;
str LINES[] = {};

char *ELANG_FUNCTIONS[] = { "println" };

int numberOfeLangFunctions = 1;

bool ignore = false;

Function FUNCTIONS[] = {};
Variable VARIABLES[] = {};