#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototype to the function that will print everything encrypted
void print_encrypted(string key, string word);

int main(int argc, char *argv[])
{
    // If we do not receive 1 argument as input (key), return 1
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // If our input do not have 26 characters, return 1
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Else we can check if the key is valid
    else
    {
        // Definition of the vector that will be used to see if a value has already appeared
        bool values[26] = {false};

        // Will go thought the entire key
        for (int i = 0; i < 26; i++)
        {
            // If the character is not alpha, return 1
            if (!isalpha(argv[1][i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }

            // Defines index as a variable that have a number between 0 and 25 to be used as index
            int index = toupper(argv[1][i]) - 'A';

            // If values[index] is defined, then the number is repeating and we return 1
            if (values[index])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }

            // Else we set values[index] as true and keep the loop
            values[index] = true;
        }
    }

    string word = get_string("plaintext: ");
    print_encrypted(argv[1], word);
    return 0;
}

void print_encrypted(string key, string word)
{
    int index;
    int len = strlen(word);
    printf("ciphertext: ");
    for (int i = 0; i < len; i++)
    {
        if (isupper(word[i]))
        {
            index = word[i] - 65;
            printf("%c", toupper(key[index]));
        }
        else if (islower(word[i]))
        {
            index = word[i] - 97;
            printf("%c", tolower(key[index]));
        }
        else
        {
            printf("%c", word[i]);
        }
    }
    printf("\n");
}
