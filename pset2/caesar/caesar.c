#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
bool only_digits(string s);

int main(int argc, string argv[])
{
    // variables
    int c;
    string word;
    int key;
    // if have only 2 args process
    if (argc == 2)
    {
        // if prompt bash is number
        if (only_digits(argv[1]))
        {
            // key is prompt but in int
            key = atoi(argv[1]);
            // prompt plain text
            word = get_string("plaintext:  ");
            printf("ciphertext: ");
            // loop between 0 and length word
            for (int i = 0, len = strlen(word); i < len; i++)
            {
                // if is  alpha and lower

                if (isalpha(word[i]) && islower(word[i]))
                {
                    // position char plus key module 97 view position move ,
                    // modulo 26 by limit changes
                    c = ((word[i] + key) % 97) % 26;
                    // position plus 97(a)
                    printf("%c", c + 97);
                }
                // same logic but uppercase
                else if (isalpha(word[i]) && isupper(word[i]))
                {
                    c = ((word[i] + key) % 65) % 26;

                    printf("%c", c + 65);
                }
                else
                {
                    printf("%c", word[i]);
                }
            }
            printf("\n");
            return 0;
        }
        else
        {
            printf("Usage: ./caesar key");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }

}

// func
bool only_digits(string s)
{
    // get string and loop
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        // if is not digit break loop and false else is true
        if (isdigit(s[i]) == 0)
        {
            return false;
            break;
        }

    }
    return true;
}