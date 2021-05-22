// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word
    int index = hash(word);
    // Access linked list at the hashed index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Traverse the linked list looking for the word (strcasecmp)
        if (strcasecmp(cursor->word, word) == 0)
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
    // Purloined from "djb2" here: http://www.cse.yorku.ca/~oz/hash.html
    // Created by Dan Bernstein.
    unsigned long hash = 5381;
    int c = 0;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N;
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
    char value[LENGTH + 1];
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
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
