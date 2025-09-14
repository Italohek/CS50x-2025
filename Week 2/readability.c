#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Get text input from user and initialize counters
    string text = get_string("Text: ");
    int len = strlen(text);
    int counter = 0, sentences = 0, words = 1;

    // Loop through each character in the text
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        else if (isalpha(text[i]))
        {
            counter++;
        }
    }

    // Calculate the Coleman-Liau index by determining L and S as
    // L = average number of letters per 100 words
    // S = average number of sentences per 100 words
    float L = ((counter * 1.0) / words) * 100;
    float S = ((sentences * 1.0) / words) * 100;
    int index = round(((0.0588 * L) - (0.296 * S) - 15.8));

    // Print the grade level based on the index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 15)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
    return 0;
}
