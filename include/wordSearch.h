#ifndef WORD_SEARCH
#define WORD_SEARCH

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int populateVertical(char **wordSearch, int width, int height, char *word, int depth);
int populateHorizontal(char **wordSearch, int width, int height, char *word, int depth);
int populate(char **wordSearch, int width, int height, char **solution, char **words, int wordCount);

#endif