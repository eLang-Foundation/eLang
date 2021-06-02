#ifndef GET_H
#define GET_H

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif
char *get(char *string, char *pattern);
bool match(char *string, char *pattern);
#ifdef __cplusplus
}
#endif

#endif
