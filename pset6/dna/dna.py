"""
CS50 Problem Set 6: DNA
-----------------------
Implement a program that identifies a person based on their DNA, per the
below.

$ python dna.py databases/large.csv sequences/5.txt
Lavender

* The first argument will be a CSV file with STR counts for individuals.
* The second argument will be a file of the DNA sequence to identify.
  * If not, the program should print an error message.
* Open the CSV file and read its contents into memory.
* The first row of the CSV file will be the column names.
* Open the DNA sequence and read its contents into memory.
* Compute the longest consecutive repeats of the STR to identify.
* If counts match with any in the CSV file, print the name.
* Assume the STR counts will not match more than one individual.
* If the STR counts do not match exactly, print "No match".
"""
import csv
from collections import defaultdict
from sys import argv, exit


class Sequencer:
    """Assesses sequences of DNA for identifying individuals."""

    def __init__(self, raw_sequence, str_keys):
        """Constructs sequencer and maps str keys to an internal dict
        for processing.

        args:
            raw_sequence (str): the DNA strand to check for patterns.
            strs_keys (list[str]): list of the particular str patterns
                to look for in the sequence.
        """
        self.raw_sequence = raw_sequence
        self.str_counts_map = defaultdict(int)
        # Don't know how many STRs we'll get.
        for k in str_keys:
            self.str_counts_map[k]

    def sequence(self, profiles):
        """Examines the sequence for the str keys in strs_map and
        compares str counts to profiles, returning a match if there is
        one.
        """
        for dna_str in self.str_counts_map.keys():
            # Assign STR counts.
            self.str_counts_map[dna_str] = self._count_strs(dna_str)

        for profile in profiles:
            # If all of the STR counts for the sequence match the profile under
            # examination, we got a match!
            if all(
                profile[str_key] == str(str_count)
                for str_key, str_count in self.str_counts_map.items()
            ):
                return profile["name"]
        # We got through all the profiles without a match.
        return "No match"

    def _count_strs(self, dna_str):
        """For a given dna_str, find the number of consecutive
        occurences of the str in a sequence of DNA.

        args:
            dna_str (str): the particular str to count.

        returns: (int)
        """
        largest_count = 0
        # Given an STR of a variable size, let's iterate through the sequence looking
        # for that pattern.
        for i in range(len(self.raw_sequence) - len(dna_str) + 1):
            count = 0
            # We want to look ahead in the sequence without losing our place, so copy
            # the current index.
            j = i
            while self.raw_sequence[j: j + len(dna_str)] == dna_str and len(
                dna_str
            ) < len(self.raw_sequence):
                # Increment our match count for each consecutive chunk that matches.
                count += 1
                j += len(dna_str)

            if count > largest_count:
                # If it is the largest string we've encountered, update our largest.
                largest_count = count

        return largest_count


def main():
    """Identifies a person based on their DNA."""
    if len(argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    with open(argv[1]) as f:
        profiles = [profile for profile in csv.DictReader(f)]

    with open(argv[2]) as f:
        sequence = f.read()

    sequencer = Sequencer(
        sequence,
        [k for k in profiles[0].keys() if k != "name"],
    )

    print(sequencer.sequence(profiles))


if __name__ == "__main__":
    main()
