#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }
    // Make sure every character in argv[1] is a digit

    string s = argv[1];
    bool digits = only_digits(s);
    if (!digits)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }
    // Convert argv[1] from a `string` to an `int`

    int k = atoi(s);

    // Prompt user for plaintext

    string text = get_string("plaintext: ");
    // For each character in the plaintext:
    printf("ciphertext: ");
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                printf("%c", ((text[i] - 65) + k) % 26 + 65);
            }
            else if (islower(text[i]))
            {
                printf("%c", ((text[i] - 97) + k) % 26 + 97);
            }
        }
        else
        {
            text[i] = text[i];
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}

bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}
