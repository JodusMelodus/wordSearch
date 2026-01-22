#include "wordSearch.h"

int populateVertical(char **wordSearch, int width, int height, char *word, int depth)
{
    if (depth <= 0)
    {
        printf("Failed to add word \"%s\", no space found.\n", word);
        return 1;
    }

    int len = strlen(word);
    int x = rand() % width;
    int y = rand() % (height - len);

    for (int i = 0; i < len; i++)
        if (wordSearch[y + i][x] != '.' && wordSearch[y + i][x] != word[i])
            return populateVertical(wordSearch, width, height, word, depth - 1);

    for (int i = 0; i < len; i++)
        wordSearch[y + i][x] = word[i];
    return 0;
}

int populateHorizontal(char **wordSearch, int width, int height, char *word, int depth)
{
    if (depth <= 0)
    {
        printf("Failed to add word \"%s\", no space found.\n", word);
        return 1;
    }

    int len = strlen(word);
    int x = rand() % (width - len);
    int y = rand() % height;

    for (int i = 0; i < len; i++)
        if (wordSearch[y][x + i] != '.' && wordSearch[y][x + i] != word[i])
            return populateHorizontal(wordSearch, width, height, word, depth - 1);

    for (int i = 0; i < len; i++)
        wordSearch[y][x + i] = word[i];
    return 0;
}

int populate(char **wordSearch, int width, int height, char **solution, char **words, int wordCount)
{
    srand(time(NULL));

    // Initialize grid
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            wordSearch[y][x] = '.';

    // Populate grid
    for (int i = 0; i < wordCount; i++)
    {
        char *word = words[i];
        int direction = rand() % 2; // 0: Vertical, 1: Horizontal

        if (direction == 0)
            populateVertical(wordSearch, width, height, word, 10);
        else
            populateHorizontal(wordSearch, width, height, word, 10);
    }

    for (int i = 0; i < height; i++)
        memcpy(solution[i], wordSearch[i], width * sizeof(char));

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            if (wordSearch[y][x] == '.')
                wordSearch[y][x] = 'A' + rand() % 26;

    return 0;
}
