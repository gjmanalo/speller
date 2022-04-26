// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 52;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int Hashindex = hash(word);
    node *cursor = table[Hashindex];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int n = 0;
    if (strlen(word) > 1)
    {
    n = (tolower(word[1]) - 'a');
    }
    return (tolower(word[0]) - 'a') + (n % N);
}

// Loads dictionary into memory, returning true if successful, else false
int numberofwords = 0;
bool load(const char *dictionary)
{
    // TODO
    unsigned int Hashindex;
    FILE *file = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
    return false;
    }

    char temp[LENGTH + 1];

    while(fscanf(file, "%s", temp) != EOF)
    {
    node *n  = malloc(sizeof(node));
    if (n == NULL)
    {
    return false;
    }
    strcpy(n -> word, temp);
    Hashindex = hash(temp);
    //printf("%i", Hashindex);
    n -> next = table[Hashindex];
    table[Hashindex] = n;
    numberofwords++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numberofwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int Hashindex = 0;
    node *cursor = table[Hashindex];
    while (Hashindex < N)
    {
    cursor = table[Hashindex];
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    Hashindex++;
    }
return true;
}
