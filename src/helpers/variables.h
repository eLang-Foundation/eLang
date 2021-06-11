#define ui unsigned int
#define ERROR_MSG "Error"
#define FND "Undefined function"
#define VND "Undefined variable"
#define INV "Invalid value"
#define INS "Invalid syntax"

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
	char *type;
} Variable;

// global variables
char *FILENAME;
char *CONTENTS;
strArray LINES;

char *ELANG_FUNCTIONS[] = { "print", "println" };

int numberOfeLangFunctions = 2;

bool ignore = false;

Function *FUNCTIONS;
Variable *VARIABLES;

int numberOfFunctions, numberOfVariables, lineNumber;

int lastIfStatement = -1;
