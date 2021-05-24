"""
CS50 Problem Set 6: Mario
-------------------------
Implement a program that prints out a double half-pyramid of a
specified height, per the below.

$ python mario.py
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
"""
from cs50 import get_int


def main():
    """Ask the user for a height, and then print out a double pyramid
    of a given size.
    """
    while True:
        height = get_int("Height: ")
        # Make sure the number meets the requirements.
        if height < 9 and height > 0:
            break

    for i in range(1, height + 1):
        # Make sure we have the right indentation.
        indentation = ""
        # If the level will be offset ...
        if height - i:
            # Add space.
            indentation += " " * (height - i)

        print(f"{indentation}{'#' * (i)}  {'#' * (i)}")


if __name__ == "__main__":
    main()
