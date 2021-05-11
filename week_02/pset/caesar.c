#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You must define 1 and only 1 encryption key!");
        return 1;
    }

    int k = atoi(argv[1]) % 26;
    string plaintext = GetString();

    for (int i = 0, l = strlen(plaintext); i < l; ++i)
    {
        int letter = plaintext[i];

        if (isalpha(letter))
        {
            int caps = isupper(letter) ? 65 : 97;
            letter = ((letter - caps + k) % 26) + caps;
        }
        printf("%c", letter);
    }
    printf("\n");

    return 0;
}
