#ifndef UTILS_H
#define UTILS_H

#define MAX_LINE_LENGTH 20

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char **readFile(const char *path, int *rowCount);
int writeFile(const char *path, char **lines, int rowCount, int colCount);

#endif