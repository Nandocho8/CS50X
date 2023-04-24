#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // defive variable
    int grade;
    string text;
    // count letters , float because this quantity will  multiply by the factor
    float l = 0;
    // count words float because this quantity will divide by the factor
    float w = 0;
    // count sentences , float because this quantity will  multiply by the factor
    float s = 0;
    // factir
    float factor = 0;
    // prompt string
    text = get_string("Text: ");
    // counts functions
    l = count_letters(text);
    w = count_words(text);
    s = count_sentences(text);
    // factor quantity will make the text simulate have 100 words
    factor = 100 / w;
    // simulate value
    l *= factor;
    // simulate value
    s *= factor;
    // the Coleman-Liau index
    grade = round(0.0588 * l - 0.296 * s - 15.8);

    // if grate between 1 and 16 print grade
    if (grade > 0 && grade < 17)
    {
        printf("Grade %i\n", grade);
    }
    // less than 1 print before grade 1
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    // greater 16+
    else
    {
        printf("Grade 16+\n");
    }
}

// func count letter
int count_letters(string text)
{
    // count letter
    int l = 0;
    // loop between 0 and len text
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        // if char is alpha plus letter
        if (isalpha(text[i]))
        {
            l++;
        }
    }
    return l;
}
// func count words
int count_words(string text)
{
    // count word through space because word start 1
    int w = 1;
    // loop between 0 and len text
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        // if char is sspace plus word
        if (isspace(text[i]))
        {
            w++;
        }
    }
    return w;
}
// func count sentences
int count_sentences(string text)
{
    // count sentences
    int s = 0;
    // loop between 0 and len text
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // count sentences through ! or . or ?
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            s++;
        }
    }
    return s;
}