#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 10
#define GRID_WIDTH 20
#define GRID_HEIGHT 20

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

int populate(char grid[GRID_HEIGHT][GRID_WIDTH], char **words, int wordCount)
{
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            grid[i][j] = '.';

    for (int i = 0; i < wordCount; i++)
    {
        char *word = words[i];
        int len = strlen(word);
        int direction = rand() % 2; // 0: Vertical, 1: Horizontal
        int x, y;

        if (direction == 0) // Vertical
        {
            x = rand() % GRID_WIDTH;
            y = rand() % (GRID_HEIGHT - len);

            for (int j = 0; j < len; j++)
                grid[y + j][x] = word[j];
        }
        else // Horizontal
        {
            x = rand() % (GRID_WIDTH - len);
            y = rand() % GRID_HEIGHT;

            for (int j = 0; j < len; j++)
                grid[y][x + j] = word[j];
        }
    }
    return 0;
}

int main()
{
    char *lines[MAX_LINES] = {0};

    int lineCount = readFile("../../words.txt", lines);
    if (lineCount == -1)
        return 1;

    char grid[GRID_HEIGHT][GRID_WIDTH];

    int res = populate(grid, lines, lineCount);

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            printf("%c", grid[y][x]);
        }
        printf("\n");
    }

    for (int i = 0; i < lineCount; i++)
        free(lines[i]);

    return 0;
}
