/**
 * CS50 Problem Set 2: Substitution
 * --------------------------------
 * Write a program called substitution that encrypts messages using a
 * substitution cipher. It takes a key from command-line argument on
 * used to encrypt the secret message. Preserve the letter casing and
 * only substitute alphabetic characters.
 */

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

string validate_args(int argc, string argv[]);
string encrypt_text(string text, string key);
char encrypt_char(char character, string key);

/**
 * Function: main
 * --------------
 * Encrypt a message using a 26-letter key provided by the user via the
 * command line.
 */
int main(int argc, string argv[])
{
    string validation_status = validate_args(argc, argv);
    if (strcmp(validation_status, "All good!") != 0)
    {
        printf("%s", validation_status);
        return 1;
    }

    string key = argv[1];
    string text = get_string("plaintext: ");
    string encrypted_text = encrypt_text(text, key);
    printf("ciphertext: %s\n", encrypted_text);
    return 0;
}

/**
 * Function: validate_args
 * -----------------------
 * Checks the validity of the submitted command line arguments and
 * returns a message to help mitigate the incorrect usage.
 */
string validate_args(int argc, string argv[])
{
    // Only one key allowed!
    if (argc != 2)
    {
        return "You must define 1 and only 1 encryption key!\n";
    }

    string key = argv[1];
    // The key must account for all English letters!
    if (strlen(key) != 26)
    {
        return "Keys must contain 26 characters.\n";
    }

    for (int i = 0, arg_length = strlen(key); i < arg_length; ++i)
    {
        // The key can only contain letters!
        if (!(isalpha(key[i])))
        {
            return "Encryption keys can only contain alphabetical characters!\n";
        }
        for (int j = i + 1, key_length = strlen(key); j < key_length; ++j)
        {
            // The key letter must be unique!
            if (key[i] == key[j])
            {
                return "Keys must contain all 26 letters with no repeated letters!\n";
            }
        }
    }
    return "All good!";
}

/**
 * Function: encrypt_text
 * ----------------------
 * Returns a string of text encrypted with a given key.
 *
 * text (string): the text to be encrypted.
 * key (string): the key with which to encrypt the text.
 *
 * returns: (string)
 */
string encrypt_text(string text, string key)
{
    string encrypted_text = text;
    for (int i = 0, text_length = strlen(text); i < text_length; ++i)
    {
        // Get the character from the input text.
        char character = text[i];
        // If it is a letter ...
        if (isalpha(character))
        {
            character = encrypt_char(character, key);
        }
        encrypted_text[i] = character;
    }
    return encrypted_text;
}

/**
 * Function: encrypt_char
 * ----------------------
 * Return an alphabetic character encrypted with a given key.
 *
 * character (char): the character to be encrypted.
 * key (string): the key with which to encrypt the character.
 *
 * returns: (char)
 */
char encrypt_char(char character, string key)
{
    // Capture the case of the current text character.
    int char_caps_value = isupper(character) ? 65 : 97;
    int char_base_index = character - char_caps_value;

    // Capture the case of the key character.
    int key_caps_value = isupper(key[char_base_index]) ? 65 : 97;
    // Get the key equivalent of the current character
    int key_base_index = key[char_base_index] - key_caps_value;

    // Apply the proper caps value to the newly encrypted character.
    return key_base_index + char_caps_value;
}