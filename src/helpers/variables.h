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
	char *scope;
	bool constant;
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

char *lastReturnValue = "Null";

char *SCOPE = "";

bool EXIT_WHEN_ERROR = true;
