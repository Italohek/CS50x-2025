#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Definition of the table of values and the two integers that will be used to compare both
    // players
    int values[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int pointsA = 0;
    int pointsB = 0;

    // Input of the first and second players
    string first_word = get_string("Player 1: ");
    string second_word = get_string("Player 2: ");

    // Integers representing the lenght of their inputs
    int len_fw = strlen(first_word);
    int len_sw = strlen(second_word);

    // Loop that calculates if the current character is in the expected value in the ascii table. If
    // it is, sum points A by going to the values[letter]
    for (int j = 0; j < len_fw; j++)
    {
        int letter = toupper(first_word[j]) - 65;
        if (letter >= 0 && letter <= 25)
        {
            pointsA += values[letter];
        }
    }

    // Loop that calculates if the current character is in the expected value in the ascii table. If
    // it is, sum points B by going to the values[letter]
    for (int j = 0; j < len_sw; j++)
    {
        int letter = toupper(second_word[j]) - 65;
        if (letter >= 0 && letter <= 25)
        {
            pointsB += values[letter];
        }
    }

    // Compare the points of the two and see which one is bigger
    if (pointsB > pointsA)
    {
        printf("Player 2 wins!\n");
    }
    else if (pointsB < pointsA)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return 0;
}
