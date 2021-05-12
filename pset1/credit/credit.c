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
#include <math.h>

// Result types.
const string VISA = "VISA\n";
const string AMEX = "AMEX\n";
const string MASTERCARD = "MASTERCARD\n";
const string INVALID = "INVALID\n";

/**
 * Function: get_digit_number
 * --------------------------
 * Returns the number of digits a given number has.
 *
 * number: the long to process.
 *
 * returns: int number of digits in number.
 */
int get_number_of_digits(long number)
{
    int number_of_digits = 0;
    do
    {
        // Chip away at number until it runs out of digits.
        // Decimal values are truncated in C.
        number /= 10;
        number_of_digits += 1;
    }
    while (number > 0);

    return number_of_digits;
}

/**
 * Function: is_valid_by_checksum
 * --------------------------
 * Returns whether or not the number is a valid credit card number
 * based on Luhn's Algorithm.
 *
 * number (long): the number under investigation.
 *
 * returns (bool)
 */
bool is_valid_by_checksum(long number)
{
    // The first digit we process will be the last digit, which we never multiply by 2.
    bool multiply_by_two = false;
    int checksum = 0;
    do
    {
        int digit = number % 10;
        if (multiply_by_two)
        {
            digit *= 2;
            do
            {
                int product_digit = digit % 10;
                checksum += product_digit;
                digit /= 10;
            }
            while (digit > 0);
        }
        else
        {
            checksum += digit;
        }
        // Lop the digit off of our number.
        number /= 10;
        // whatever we did this time, do the opposite next time.
        multiply_by_two = !multiply_by_two;
    }
    while (number > 0);

    // If the total’s last digit is 0, the number is valid!
    return checksum % 10 == 0;
}

/**
 * Function: get_first_two_digits
 * ------------------------------
 * Returns the first two digits of a number as an int.
 *
 * number: the number whose first digits will be returned.
 * number_of_digits: how many digits the number has.
 *
 * returns: int of first two digits.
 */
int get_first_two_digits(long number, int number_of_digits)
{

    float digit_truncator = pow(10.0, ((float)(number_of_digits - 2)));
    return number / digit_truncator;
}

/**
 * Function: determine_card_type
 * -----------------------------
 * Determine what kind of credit the number is or if it is invalid.
 *
 * number (long): the possible credit card number.
 * number_of_digits (int): the number of digits in number.
 *
 * returns (string) credit card type.
 */
string determine_card_type(long number, int number_of_digits)
{
    if (is_valid_by_checksum(number))
    {
        int first_digits = get_first_two_digits(number, number_of_digits);

        bool in_visa_range = (number_of_digits < 17 && number_of_digits > 12);
        bool in_amex_range = number_of_digits == 15;
        bool in_mastercard_range = number_of_digits == 16;

        if (in_visa_range && (first_digits > 39 && first_digits < 50))
        {
            return VISA;
        }
        else if (in_amex_range && (first_digits == 34 || first_digits == 37))
        {
            return AMEX;
        }
        else if (in_mastercard_range && (first_digits > 50 && first_digits < 56))
        {
            return MASTERCARD;
        }
    }

    // If we didn't match above, the number is no good.
    return INVALID;
}

/**
 * Function: main
 * --------------
 * Verify the validity of a credit card number.
 */
int main(void)
{
    // Get input that is at least as long as it needs to be.
    long number;
    int number_of_digits;

    number = get_long("Number: ");
    // Determine how long the number is.
    number_of_digits = get_number_of_digits(number);

    string result = determine_card_type(number, number_of_digits);
    printf("%s", result);
}
