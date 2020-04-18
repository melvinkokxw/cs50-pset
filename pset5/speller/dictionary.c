// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 2048;

// Hash table
node *table[N];

// Word count loaded in dictionary
unsigned int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash word to get hash value
    unsigned int hashValue = hash(word);

    node *trav = table[hashValue];

    // Traverse through linked list at relevant index to find word strcasecmp
    while (trav != NULL)
    {
        // If word matched, return true
        if (strcasecmp(word, trav->word) == 0)
        {
            return true;
        }

        trav = trav->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // adapted djb2 algorithm from http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }

    hash %= N;

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to load dictionary");
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *entry = malloc(sizeof(node));
        if (entry == NULL)
        {
            free(entry);
            printf("Unable to create new node");
            return false;
        }

        // Copy word into node
        strcpy(entry->word, word);

        // Hash word to obtain hash value
        unsigned int hashValue = hash(entry->word);

        // If assigned table slot is empty, assign node to table slot
        if (table[hashValue] == NULL)
        {
            entry->next = NULL;
            table[hashValue] = entry;
        }

        // Otherwise point entry->next to current table value, then assign node to table slot
        else
        {
            entry->next = table[hashValue];
            table[hashValue] = entry;
        }

        wordcount++;
    }

    // Close dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0 ; i < N ; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }

        for (node *trav = table[i], *travNext = table[i] ; trav != NULL ; trav = travNext)
        {
            travNext = trav->next;
            free(trav);
        }
    }
    return true;
}
