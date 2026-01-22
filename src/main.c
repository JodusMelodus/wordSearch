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

int writeFile(const char *path, char grid[GRID_HEIGHT][GRID_WIDTH])
{
    FILE *file = fopen(path, "w");
    if (!file)
    {
        perror("Failed to open file");
        return -1;
    }

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            fputc(grid[y][x], file);
            fputc(' ', file);
        }
        fputc('\n', file);
    }

    fclose(file);
    printf("Grid successfully saved to %s\n", path);
    return 0;
}

int populateVertical(char grid[GRID_HEIGHT][GRID_WIDTH], char *word, int depth)
{
    if (depth <= 0)
        return 1;

    int len = strlen(word);
    int x = rand() % GRID_WIDTH;
    int y = rand() % (GRID_HEIGHT - len);

    for (int j = 0; j < len; j++)
        if (grid[y + j][x] != '.' && grid[y + j][x] != word[j])
            return populateVertical(grid, word, depth - 1);

    for (int j = 0; j < len; j++)
        grid[y + j][x] = word[j];
    return 0;
}

int populateHorizontal(char grid[GRID_HEIGHT][GRID_WIDTH], char *word, int depth)
{
    if (depth <= 0)
        return 1;

    int len = strlen(word);
    int x = rand() % (GRID_WIDTH - len);
    int y = rand() % GRID_HEIGHT;

    for (int j = 0; j < len; j++)
        if (grid[y][x + j] != '.' && grid[y][x + j] != word[j])
            return populateHorizontal(grid, word, depth - 1);

    for (int j = 0; j < len; j++)
        grid[y][x + j] = word[j];
    return 0;
}

int populate(char wordSearch[GRID_HEIGHT][GRID_WIDTH], char solution[GRID_HEIGHT][GRID_WIDTH], char **words, int wordCount)
{
    srand(time(NULL));

    // Copy grid
    char copy[GRID_HEIGHT][GRID_WIDTH];
    memcpy(copy, wordSearch, sizeof(wordSearch));

    // Initialize grid
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            copy[i][j] = '.';

    for (int i = 0; i < wordCount; i++)
    {
        char *word = words[i];
        int len = strlen(word);
        int direction = rand() % 2; // 0: Vertical, 1: Horizontal
        int x, y;

        if (direction == 0) // Vertical
        {
            populateVertical(copy, word, 5);
        }
        else // Horizontal
        {
            populateHorizontal(copy, word, 5);
        }
    }

    // Copy back to word search and solution
    memcpy(wordSearch, copy, sizeof(copy));
    memcpy(solution, copy, sizeof(copy));

    for (int y = 0; y < GRID_HEIGHT; y++)
        for (int x = 0; x < GRID_WIDTH; x++)
            if (wordSearch[y][x] == '.')
                wordSearch[y][x] = 'A' + rand() % 26;

    return 0;
}

int main()
{
    char *lines[MAX_LINES] = {0};

    int lineCount = readFile("../../words.txt", lines);
    if (lineCount == -1)
        return 1;

    char wordSearch[GRID_HEIGHT][GRID_WIDTH];
    char solution[GRID_HEIGHT][GRID_WIDTH];

    int res = populate(wordSearch, solution, lines, lineCount);
    if (res == -1)
        return 1;

    res = writeFile("../../word_search.txt", wordSearch);
    if (res == -1)
        return 1;
    res = writeFile("../../solution.txt", solution);
    if (res == -1)
        return 1;

    for (int i = 0; i < lineCount; i++)
        free(lines[i]);

    return 0;
}
