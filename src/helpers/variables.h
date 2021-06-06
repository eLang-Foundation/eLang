#define ui unsigned int
#define FND "Function not defined"
#define VND "Variable not defined"

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

char *ELANG_FUNCTIONS[] = { "print", "println" };

int numberOfeLangFunctions = 2;

bool ignore = false;

Function FUNCTIONS[];
Variable VARIABLES[] = {};
