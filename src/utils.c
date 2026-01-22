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
    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        char **temp = realloc(lines, (count + 1) * sizeof(char *));
        if (!temp)
        {
            for (int i = 0; i < count; i++)
                free(lines[i]);
            free(lines);
            fclose(file);
            return NULL;
        }
        lines = temp;
        lines[count] = strdup(buffer);
        lines[count][strcspn(lines[count], "\r\n")] = 0;
        for (int i = 0; lines[count][i]; i++)
            lines[count][i] = toupper((unsigned char)lines[count][i]);
        count++;
    }

    fclose(file);
    *rowCount = count;
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