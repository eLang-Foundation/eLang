// structs
typedef struct
{
	char **array;
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

char *lastReturnValue;

char *SCOPE = "";

bool EXIT_WHEN_ERROR = true;

char NEW_LINE_SEPARATOR = '~';

bool IF_STATEMENT = false;
