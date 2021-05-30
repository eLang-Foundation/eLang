#define ui unsigned int

// structs
typedef struct
{
	char *value;
	bool allocated;
} str;

typedef struct
{
	char *name;
	char *arguments;
	char *code;
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
char *ELANG_FUNCTIONS[] = { "print" };

bool ignore = false;

Function FUNCTIONS[] = {};
Variable VARIABLES[] = {};
