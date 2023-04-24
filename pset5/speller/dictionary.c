
// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
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

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

//
int countDic =0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // i use same form to hexadec first letter with a to 1 and second a to 0
    int pos = 0;
    for(int i = 0; word[i]!='\0' ; i++)
    {
        pos += tolower(word[i]);
    }
    return pos % N;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // find position
    int pos = hash(word);
    // define cursor
    node *cursor = table[pos];
    while ( cursor!= NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open file
    FILE *file = fopen(dictionary, "r");
    // is null out
    if (file == NULL)
    {
        return false;
    }
    // buffer read
    char buffer[LENGTH + 1];
    // open file

    // loop scan all words
    while (fscanf(file, "%s", buffer) != EOF)
    {

        // get memory
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // implemento hash function
        int hash_number = hash(buffer);
        // copy buffer en word
        strcpy(n->word, buffer);
        if (table[hash_number] != NULL)
        {
            // asigno el nuevo next a la tabla existente
            n->next = table[hash_number];
            // y la tabla existente la cambio a n
            table[hash_number] = n;
        }
        else
        {
            // asigno el nuevo next a la tabla existente
            n->next = NULL;
            // y la tabla existente la cambio a n
            table[hash_number] = n;
        }
        // aumento count
        countDic++;
        // if table[i] is not null

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (countDic > 0)
    {
        return countDic;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while(cursor != NULL)
        {
            node *temp = table[i];
            cursor = cursor->next;
            free(temp);
        }
        if (i == N-1 && cursor == NULL)
        {
            return true;
        }
    table[i] = NULL;
    free (cursor);
    }
    return false;
}
