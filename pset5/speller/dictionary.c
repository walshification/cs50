// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Read dictionary words into nodes.
    char value[LENGTH];
    while (fscanf(file, "%s", value) != EOF)
    {
        node *n = malloc(sizeof(node));
        // If memory error ...
        if (n == NULL)
        {
            return false;
        }
        // Copy dictionary value into node word slot.
        strcpy(n->word, value);
        n->next = NULL;
        // Hash word.
        int index = hash(value);
        // Insert node into hash table at hashed value.
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            // Point the new node at the existing node at the index.
            n->next = table[index];
            // Slot in the new node.
            table[index] = n;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
