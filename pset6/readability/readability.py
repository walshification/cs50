"""
CS50 Problem Set 6: Readability
-------------------------------
Author: Christopher Walsh
GitHub username: walshification

Write a program that takes a text and determines its reading level,
using the Coleman-Liau index to calculate grade level:

index = 0.0588 * L - 0.296 * S - 15.8

Where L is the average number of letters per 100 words and S is the
average number of sentences per 100 words.

Prompt the user for a string of text (using get_string).
Print "Grade X" for the computed level X, rounded to the nearest int.
If the index is 16 or higher, output "Grade 16+".
If the index is less than 1, output "Before Grade 1".
"""
import re

from cs50 import get_string


class Text:
    """Representation of text with methods to gather metadata on it."""

    def __init__(self, text):
        """Constructs a text object.

        args:
            text (str): the text to be assessed.
        """
        self.raw_text = text
        self._readability_index = None

    @property
    def readability_index(self):
        """The readability index as caluclated by the Coleman-Liau
        formula for this text.
        """
        if self._readability_index is None:
            self._readability_index = self.calculate_readability()
        return self._readability_index

    def calculate_readability(self):
        """Returns the readability score as calculated with the
        Coleman-Liau formula for a given text.

        returns: (str)
        """
        letter_count = len(list(c for c in self.raw_text if c.isalpha()))
        word_count = len(self.raw_text.split())
        sentence_count = len(
            # The last value will not contain words, so filter with the conditional.
            list(
                sen
                for sen in re.split("[\.\!\?]", self.raw_text)
                if re.search(r"\w", sen)
            )
        )
        index = self._apply_coleman_liau(letter_count, word_count, sentence_count)
        return self._format(index)

    def _apply_coleman_liau(self, letter_count, word_count, sentence_count):
        """Calculate the readability index score as computed by the
        Coleman-Liau formula:

        0.0588 * L - 0.296 * S - 15.8
        where:
          * L is the average number of letters per 100 words
          * S is the average number of sentences per 100 words.

        args:
            letter_count (int): total number of letters in the text.
            word_count (int): total number of words in the text.
            sentence_count (int): total number of sentences in the text.

        returns: (int)
        """
        avg_letters_per_100_words = (letter_count * 100) / word_count
        avg_sentences_per_100_words = (sentence_count * 100) / word_count

        # Apply the magic number to our average letter count.
        avg_letter_coefficient = 0.0588 * avg_letters_per_100_words
        # Apply the magic number to our average sentence count.
        avg_sentence_coefficient = 0.296 * avg_sentences_per_100_words
        # Don't forget to round our float!
        return round((avg_letter_coefficient - avg_sentence_coefficient) - 15.8)

    def _format(self, index):
        """Formats the readability index for output.

        index (int): the Coleman-Liau readability index.

        returns: (str)
        """
        if index < 1:
            return "Before Grade 1"
        elif index > 16:
            return "Grade 16+"
        else:
            return f"Grade {index}"


def main():
    """Calulate the readibility index of a text using the Coleman-Liau
    formula, rounded to the nearest integer.
    """
    text = get_string("Text: ")
    processed_text = Text(text)
    print(processed_text.readability_index)


if __name__ == "__main__":
    main()
