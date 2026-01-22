#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "wordSearch.h"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Invalid arguments: Expected 5\n");
        printf("Usage: ./wordSearch.exe <width> <height> <path to words> <output path>\n");
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    char *path = argv[3];
    char *resultPath = argv[4];

    int lineCount = 0;
    char **lines = readFile(path, &lineCount);
    if (!lines)
        return 1;

    char **wordSearch = malloc(height * sizeof(char *));
    char **wordSearchSolution = malloc(height * sizeof(char *));

    for (int i = 0; i < height; i++)
    {
        wordSearch[i] = malloc(width * sizeof(char));
        wordSearchSolution[i] = malloc(width * sizeof(char));
    }

    populate(wordSearch, width, height, wordSearchSolution, lines, lineCount);

    save(resultPath, "word_search.txt", wordSearch, height, width);
    save(resultPath, "solution.txt", wordSearchSolution, height, width);

    for (int i = 0; i < height; i++)
    {
        free(wordSearch[i]);
        free(wordSearchSolution[i]);
    }
    free(wordSearch);
    free(wordSearchSolution);

    for (int i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }
    free(lines);

    return 0;
}

int save(char *resultPath, const char *fileName, char **wordSearch, int height, int width)
{
    int wordSearchPathLength = strlen(resultPath) + strlen(fileName) + 2;
    char *fullPath = malloc(wordSearchPathLength);

    if (!fullPath)
    {
        perror("Failed to allocate memory");
        return 1;
    }

    strcpy(fullPath, resultPath);
    if (resultPath[strlen(resultPath) - 1] != '/')
        strcat(fullPath, "/");
    strcat(fullPath, fileName);
    writeFile(fullPath, wordSearch, height, width);
    free(fullPath);
    return 0;
}
