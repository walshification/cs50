/**
 * CS50 Problem Set 1: Mario
 * -------------------------
 * Recreate the pyramids from the Super Mario Bros. level 1-1 in C,
 * using hashes (#) for bricks. For example:
 *
 *    #  #
 *   ##  ##
 *  ###  ###
 * ####  ####
 *
 * Allow the user to input the height of the pyramids by prompting
 * them for a positive integer between 1 and 8, inclusive.
 */

#include <stdio.h>
#include <cs50.h>

/**
 * Function: get_height
 * --------------------
 * Returns a number from the user between 0 and 9.
 * 
 * returns: the user-inputted number.
 */
int get_height(void)
{
    int height;
    do
    {
        height = get_int("height: ");
    }
    // Ensure the input is within the proper bounds.
    while (height < 1 || height > 8);

    return height;
}

/**
 * Function: pad_left
 * ------------------
 * Prints the necessary padding on the left of the prompt to make a
 * nice triangluar shape.
 * 
 * height: the current height we are at in the pyramid.
 */
void pad_left(int height)
{
    // Indent as many spaces as it is high, minus 1.
    for (int i = height - 1; i > 0; i--)
    {
        printf(" ");
    }
}

/**
 * Function lay_step_bricks
 * ------------------------
 * Prints a # brick for the provided length.
 * 
 * length: how long the row should be.
 */
void lay_step_bricks(int length)
{
    // Drop a brick.
    for (int i = length; i > 0; i--)
    {
        printf("#");
    }
}


/**
 * Function construct_row
 * ----------------------
 * Builds a row of the pyramids of a given height and length, ensuring
 * they are padded properly on the left, and have the correct gap.
 * 
 * height: the current height of the pyramids.
 * length: how long the row in a single pyramid should be.
 */
void construct_row(int height, int length)
{
    pad_left(height);
    lay_step_bricks(length);
    printf("  ");  // add gap
    lay_step_bricks(length);
    printf("\n");  // end the row
}


/**
 * Function main
 * -------------
 * Print a pair of pyramids of a given height.
 */
int main(void)
{
    int height = get_height();
    int length = 1;
    while (height > 0)
    {
        construct_row(height, length);

        height--;
        length++;
    }
}
