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

    string k = argv[1];
    for (int c = 0, l = strlen(k); c < l; ++c)
    {
        if (!(isalpha(k[c])))
        {
            printf("Encryption keys can only contain alphbetical characters!");
            return 1;
        }
    }

    string plaintext = GetString();

    int j = 0;
    int keylength = strlen(k);
    for (int i = 0, l = strlen(plaintext); i < l; ++i)
    {
        int letter = plaintext[i];
        if (isalpha(letter))
        {
            int letter_caps = isupper(letter) ? 65 : 97;
            int key_caps = isupper(k[j]) ? 65 : 97;
            int key = k[j] - key_caps;
            int base_letter = (letter - letter_caps) % 26;
            letter = ((base_letter + key) % 26) + letter_caps;
            j = (j + 1) % keylength;
        }
        printf("%c", letter);
    }
    printf("\n");

    return 0;
}
