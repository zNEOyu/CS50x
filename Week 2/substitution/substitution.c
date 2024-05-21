#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }

    string s = argv[1];
    // key length
    if (strlen(s) != 26)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }
    // check for non-alph char
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isalpha(s[i]))
        {
        }
        else
        {
            printf("Usage: ./caesar key\n");

            return 1;
        }
    }
    // check for repeated char
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (tolower(s[i]) == tolower(s[j]))
            {
                printf("Usage: ./caesar key\n");

                return 1;
            }
        }
    }
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (islower(s[i]))
        {
            s[i] = s[i] - 32;
        }
    }
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    // for each alpha, what letter map
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char ctext[len + 1];

        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                int letter = text[i] - 65;
                printf("%c", s[letter]);
            }
            else if (islower(text[i]))
            {
                int letter = text[i] - 97;
                printf("%c", s[letter] + 32);
            }
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
