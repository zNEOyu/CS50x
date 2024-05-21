#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text

    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text

    int l = count_letters(text);
    int w = count_words(text);
    int s = count_sentences(text);
    // Compute the Coleman-Liau index

    float M = 100.00 * l / w;
    float T = 100.00 * s / w;
    float index = 0.0588 * M - 0.296 * T - 15.8;
    // Print the grade level

    if (0 < (int) round(index) && (int) round(index) < 16)
    {
        printf("Grade %i\n", (int) round(index));
    }

    else if (1 > (int) round(index))
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char lower_char = tolower(text[i]);
        if (lower_char == '.' || lower_char == '!' || lower_char == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
