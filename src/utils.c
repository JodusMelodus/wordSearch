#include "utils.h"

char **readFile(const char *path, int *rowCount)
{
    FILE *file = fopen(path, "r");
    if (!file)
    {
        perror("Failed to open file");
        return NULL;
    }

    char **lines = NULL;
    char buffer[256];
    int lineCount = 0;

    while (fscanf(file, "%255[a-zA-Z]", buffer) == 1)
    {
        char **temp = realloc(lines, (lineCount + 1) * sizeof(char *));
        if (!temp)
        {
            for (int i = 0; i < lineCount; i++)
                free(lines[i]);
            free(lines);
            fclose(file);
            return NULL;
        }
        lines = temp;
        lines[lineCount] = strdup(buffer);
        for (int i = 0; lines[lineCount][i]; i++)
            lines[lineCount][i] = toupper((unsigned char)lines[lineCount][i]);
        lineCount++;

        int c;
        while ((c = fgetc(file)) != EOF && !isalpha(c))
            ;
        if (c != EOF)
            ungetc(c, file);
    }

    fclose(file);
    *rowCount = lineCount;
    return lines;
}

int writeFile(const char *path, char **lines, int rowCount, int colCount)
{
    FILE *file = fopen(path, "w");
    if (!file)
    {
        perror("Failed to open file");
        return -1;
    }

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            fputc(lines[i][j], file);
            fputc(' ', file);
        }
        fputc('\n', file);
    }

    fclose(file);
    return 0;
}