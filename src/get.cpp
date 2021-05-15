#include <stdio.h>
#include <string.h>
#include <regex>
#include "get.h"

// this function returns the string found using given regex pattern
extern "C" char *get(char *string, char *pattern);
