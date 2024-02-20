// Implements a dictionary's functionality

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 20000;

// Hash table
node *table[N];

// Initialize word counter to 0
int wordCounter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word
    int hashIndex = hash(word);

    // Create a cursor to look through table
    node *cursor = table[hashIndex];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Find bucket range based on the first letter of the word
    int letter1 = (int)toupper(word[0]) - 65;
    int hashStart = (letter1 * 26) + 1;

    if (strlen(word) > 1)
    {
        int letter2 = (int)toupper(word[1]) - 65;
        hashStart += letter2;
    }

    return hashStart;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");

    // Return false if file can't be opened
    if (dict == NULL)
    {
        printf("Could not open %s.", dictionary);
        return false;
    }
    else if (dict != NULL)
    {
        // Load word into hash table
        char dictWord[LENGTH + 1];
        int hashIndex = 0;
        while (fscanf(dict, "%s", dictWord) != EOF)
        {
            node *n = malloc(sizeof(node));

            if (n == NULL)
            {
                return false;
                break;
            }
            else
            {
                // Copy word to temporary node
                strcpy(n->word, dictWord);
                n->next = NULL;

                // Find hash index for that word
                hashIndex = hash(dictWord);

                // Add temporary node to hash table
                if (table[hashIndex] == NULL)
                {
                    table[hashIndex] = n;
                }
                else
                {
                    n->next = table[hashIndex];
                    table[hashIndex] = n;
                }

                wordCounter++;
            }
        }
        fclose(dict);
        return true;
    }
    else
    {
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];

        while (tmp != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
