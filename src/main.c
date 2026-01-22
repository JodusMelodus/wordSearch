#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10

int readFile(const char *path, char **lines)
{
    FILE *file = fopen(path, "r");
    if (!file)
    {
        perror("Failed to open file");
        return -1;
    }

    char lineBuffer[1024];
    int count = 0;

    while (count < MAX_LINES && fgets(lineBuffer, sizeof(lineBuffer), file))
    {
        lineBuffer[strcspn(lineBuffer, "\n")] = '\0';
        lines[count] = strdup(lineBuffer);
        count++;
    }

    fclose(file);
    return count;
}

int main()
{
    char *lines[MAX_LINES] = {0};

    int lineCount = readFile("../../words.txt", lines);
    if (lineCount == -1)
        return 1;

    for (int i = 0; i < lineCount; i++)
        printf("%d: %s\n", i + 1, lines[i]);

    for (int i = 0; i < lineCount; i++)
        free(lines[i]);

    return 0;
}
