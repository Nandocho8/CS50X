
// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
unsigned int hash(const char *word);
int main(void)
{
    int i = hash("bzala");
    printf("pos %i\n", i);
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // i use same form to hexadec first letter with a to 1 and second a to 0
    int first = toupper(word[0]) - '@';
    int second = toupper(word[1]) - 'A';
    int position = (second) + ((first)*26);
    return position;
}
