"""
CS50 Problem Set 6: Credit
--------------------------
Implement a program that determines whether a provided credit card
number is valid according to Luhn’s algorithm.

$ python credit.py
Number: 378282246310005
AMEX
"""
import re

from cs50 import get_int


CARD_TYPES_TO_PATTERNS = {
    "AMEX": re.compile(r"^3[4|7]{1}(?:\d){13}$"),
    "MASTERCARD": re.compile(r"^5[1-5]{1}(?:\d){14}$"),
    "VISA": re.compile(r"^4(?:\d){12,15}"),
}


class CreditCard:
    """Representation of a credit card with validation methods."""

    def __init__(self, number):
        """
        Constructs a potential credit card type from a number.

        args:
            number (int): the potential credit card number.
        """
        self.number = number

    def determine_type(self):
        """
        Validates a given card number and returns the type it
        corresponds to or INVALID.

        returns: (bool)
        """
        if card_type := self._passes_luhn() and self._card_match():
            return card_type
        return "INVALID"

    def _passes_luhn(self):
        """
        Applies Luhn's Algorithm to the provided credit card number and
        determines its validity.

        returns: (bool)
        """
        # Multiple every other digit by two, starting with the second-to-last digit.
        every_other_times_two = [
            int(self.number[i]) * 2 for i in range(0, len(str(self.number)), -2)
        ]
        # For the doubled numbers, collect each individual digit as an int.
        doubled_digits = [
            int(digit) for number in every_other_times_two for digit in str(number)
        ]
        # Sum the doubled individual digits with the original leftover digits.
        luhn_total = sum(
            doubled_digits
            + [int(self.number[i]) for i in range(-1, len(str(self.number)), -2)]
        )
        # Is the total a multiple of 10?
        return luhn_total % 10 == 0

    def _card_match(self):
        """
        Compares number to regular expressions for card type to
        determine what potential type, if any, the number is.

        returns: (bool)
        """
        for name, pattern in CARD_TYPES_TO_PATTERNS.items():
            if pattern.match(str(self.number)):
                return name
        return None


def main():
    """Prompts the user for a credit card number, and then prints
    whether it is a valid credit card number using Luhn's algorithm,
    and, if it is, which kind.
    """
    number = get_int("Number: ")
    card = CreditCard(number)
    card_type = card.determine_type()
    print(card_type)


if __name__ == "__main__":
    main()
