// just want to disable CLion's warnings for strdup
#define _GNU_SOURCE

#define ui unsigned int
#define ERROR_MSG "Error"
#define FND "Undefined function"
#define INV "Invalid value"
#define INS "Invalid syntax"
#define NND "Name not defined"
#define WARN "Warning"


// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#include "helpers/variables.h"

// C++ functions
extern char *get(char *, char *);
extern bool match(char *, char *);

// function prototypes
void functionCall(char *line, char *after);
char *evaluate(char *expression, bool mathematicalExpression);
char *trim(char *string);
char *type(char *value);
char *getValue(char *string);
double calculate(char *expression);
double toNumber(char *string);

// helper files
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
#include "helpers/remove.c"
#include "helpers/getValue.c"
#include "helpers/calculate.c"

// eLang functions
#include "stdlib/numberable.c"
#include "stdlib/type.c"
#include "stdlib/toNumber.c"
#include "stdlib/toString.c"
#include "stdlib/toBool.c"
#include "stdlib/evaluate.c"
#include "stdlib/print.c"

// the if statement function
#include "helpers/ifStatement.c"
// the execute function
#include "helpers/execute.c"
// the functionCall function
#include "helpers/functionCall.c"

// logo in ascii
#include "../logo/logo.h"

// the setup file
#include "helpers/setup.c"
