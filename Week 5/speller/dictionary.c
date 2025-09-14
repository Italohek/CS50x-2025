// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 65536;
unsigned int counter, hash_value;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Tell us which linked list to search
    hash_value = hash(word);

    // Starts the cursor at the beginning of the list
    node *cursor = table[hash_value];

    // Loop through the linked list until NULL is reached
    while (cursor != NULL)
    {
        // Compare two strings in a case-insensitive comparison, return true if equals
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        // Move the cursor to the next node in the list
        cursor = cursor->next;
    }
    // Return false if the word is not in the dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Uses 5381 because that is the average by Daniel J. Bernstein hash function
    unsigned long hash;
    hash = 5381;
    int c;

    // Iterates through each character of the string as long it is not \0
    while ((c = *word++))
    {
        // Only include alphabetic characters in the hash calculation
        if (isalpha(c))
        {
            // Converts c to lower case and make everything case-insensitive.
            c = tolower(c);

            // Daniel J. Bernstein algorithm
            hash = ((hash * 33) + c);
        }
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Try to open the file
    FILE *file = fopen(dictionary, "r");

    // If file == NULL, then return false and we don't proceed.
    if (file == NULL)
    {
        return false;
    }

    // Creates a word buffer temporarily
    char word_buffer[LENGTH + 1];

    // Loop through the file until we reach the end of file
    while (fscanf(file, "%s", word_buffer) != EOF)
    {
        // For each word found, we create a new node to store in the hash table
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            // If new node == NULL, we've run out of memory and must return false
            fclose(file);
            return false;
        }
        // Copy the word from the buffer into the new node
        strcpy(new_node->word, word_buffer);

        // Determine which linked list in our hash table this word belongs to
        unsigned int index = hash(word_buffer);
        new_node->next = table[index];
        table[index] = new_node;

        // Increments counter to keep track of the dict size
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over every bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Use a cursor to go through all the hash table
        node *cursor = table[i];

        // Continue as long the cursor is not null
        while (cursor != NULL)
        {
            // Use a temporary pointer to free the memory as seen in
            // class
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    // After the loop return true
    return true;
}
