#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
const int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void print_winner(int score1, int score2);

/**
 * Function: main
 * --------------
 * Return the higher scoring of two words based on the score system of
 * Scrabble.
 */
int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    print_winner(score1, score2);
}

/**
 * Function: compute_score
 * -----------------------
 * Return the Scrabble score of a given word.
 * 
 * word (string): the word to be scored.
 * 
 * returns (int)
 */
int compute_score(string word)
{
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Normalize the letter and get its ASCII value.
        int letter_index = toupper((int)(word[i])) - 65;
        // Only add to the score if it is a l
        if (letter_index <= 26 && letter_index >= 0)
        {
            score += POINTS[letter_index];
        }

    }
    return score;
}

/**
 * Function: print_winner
 * ----------------------
 * Given scores from player 1 and player 2, print who has the highter
 * score.
 * 
 * score1 (int): Player 1's score.
 * score2 (int): Player 2's score.
 */
void print_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    };
}