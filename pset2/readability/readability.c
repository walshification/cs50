/* CS50 Problem Set 2: Readability
 * -------------------------------
 * Author: Christopher Walsh
 * GitHub username: walshification
 *
 * Write a program that takes a text and determines its reading level,
 * using the Coleman-Liau index to calculate grade level:
 *
 * index = 0.0588 * L - 0.296 * S - 15.8
 *
 * Where L is the average number of letters per 100 words and S is the
 * average number of sentences per 100 words.
 *
 * Prompt the user for a string of text (using get_string).
 * Print as output "Grade X" where X is the grade level computed by the
 *   Coleman-Liau formula, rounded to the nearest integer.
 * If the index is 16 or higher, output "Grade 16+".
 * If the index is less than 1, output "Before Grade 1".
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int calculate_readability(string text);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int apply_coleman_liau(int letter_count, int word_count, int sentence_count);

/**
 * Function: main
 * --------------
 * Calulate the readibility index of a text using the Coleman-Liau
 * formula, rounded to the nearest integer.
 */
int main(void)
{
    // Prompt user for text.
    string text = get_string("Text: ");
    // Use the Coleman-Liau formula to calculate readability.
    int index = calculate_readability(text);
    // Display index to the user.
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

/**
 * Function: calculate_readability
 * -------------------------------
 * Returns the readability score as calculated with the Coleman-Liau
 * formula for a given text.
 *
 * text (string): the text to be assessed.
 *
 * returns: (int)
 */
int calculate_readability(string text)
{
    // Count the number of letters, words, and sentences in the text.
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);
    int index = apply_coleman_liau(letter_count, word_count, sentence_count);
    return index;
}

/**
 * Function: count_letters
 * -----------------------
 * Returns the number of letters in a given text.
 *
 * text (string): the text whose letters shall be counted.
 *
 * returns: (int)
 */
int count_letters(string text)
{
    int letter_count = 0;
    for (int i = 0, text_length = strlen(text); i < text_length; i++)
    {
        // Only count letter characters.
        if (isalpha(text[i]))
        {
            letter_count++;
        }
    }
    return letter_count;
}

/**
 * Function: count_words
 * -----------------------
 * Returns the number of words in a given text.
 *
 * text (string): the text whose words shall be counted.
 *
 * returns: (int)
 */
int count_words(string text)
{
    int word_count = 0;
    for (int i = 0, text_length = strlen(text); i < text_length; i++)
    {
        // If we reach a space, we have passed a word, so count it!
        if (isspace(text[i]))
        {
            word_count++;
        }
    }
    // Add the final word, which doesn't have a space following it.
    word_count++;
    return word_count;
}

/**
 * Function: count_sentences
 * -------------------------
 * Returns the number of sentences in a given text.
 *
 * text (string): the text whose sentences shall be counted.
 *
 * returns: (int)
 */
int count_sentences(string text)
{
    int sentence_count = 0;
    for (int i = 0, text_length = strlen(text); i < text_length; i++)
    {
        char current = text[i];
        // If we reach a sentence delimiter, count it!
        if (current == '.' || current == '!' || current == '?')
        {
            sentence_count++;
        }
    }
    return sentence_count;
}

/**
 * Function: apply_coleman_liau
 * ----------------------------
 * Returns the readability index score as computed by the Coleman-Liau
 * formula: 0.0588 * L - 0.296 * S - 15.8, where L is the average
 * number of letters per 100 words and S is the average number of
 * sentences per 100 words.
 *
 * letter_count (int): total number of letters in the text.
 * word_count (int): total number of words in the text.
 * sentence_count (int): total number of sentences in the text.
 *
 * returns: (int)
 */
int apply_coleman_liau(int letter_count, int word_count, int sentence_count)
{
    float avg_letters_per_100_words = (letter_count * 100) / (float)word_count;
    float avg_sentences_per_100_words = (sentence_count * 100) / (float)word_count;

    // Apply the magic number to our average letter count.
    float avg_letter_coefficient = 0.0588 * avg_letters_per_100_words;
    // Apply the magic number to our average sentence count.
    float avg_sentence_coefficient = 0.296 * avg_sentences_per_100_words;
    // Don't forget to round our float!
    return round((avg_letter_coefficient - avg_sentence_coefficient) - 15.8);
}
