/**
 * CS50 Problem Set 1: Credit
 * -------------------------
 * Write a program that prompts the user for a credit card number and
 * then reports (via printf) whether it is a valid American Express,
 * MasterCard, or Visa card number, per the definitions of each’s
 * format herein.
 * 
 * Your program’s last line of output must be "AMEX\n" or
 * "MASTERCARD\n" or "VISA\n" or "INVALID\n".
 * 
 * For simplicity, you may assume that the user’s input will be numeric
 * (i.e., devoid of hyphens, as might be printed on an actual card).
 * But do not assume that the user’s input will fit in an int!
 * Best to use get_long from CS50’s library to get users’ input.
 */

#include <stdio.h>
#include <cs50.h>

/**
 * Function: main
 * --------------
 * Verify the validity of a credit card number.
 */
int main(void)
{
    // Result types.
    string VISA = "VISA\n";
    string AMEX = "AMEX\n";
    string MASTERCARD = "MASTERCARD\n";
    string INVALID = "INVALID\n";
    
    // Get input that is at least as long as it needs to be.
    int number;
    do
    {
        number = get_long("Number: ");
    } while (number < 4000000000000 || number > 5599999999999999);
    
    // TODO: Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    
    do
    // TODO: Add the sum to the sum of the digits that weren’t multiplied by 2.
    // TODO: If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

    string result;
    return result;
}
