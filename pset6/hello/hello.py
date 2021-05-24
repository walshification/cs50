"""
CS50 Problem Set 6: Hello
-------------------------
Implement a program that prints out a simple greeting to the user, per
the below.

$ python hello.py
What is your name?
David
hello, David
"""


def main():
    """Asks a user for their name. Prints the name, and then prints a
    hello message.
    """
    # Get the name.
    name = input("What is your name? ")
    # Here's the name.
    print(name)
    # Hello!
    print(f"hello, {name}")


if __name__ == "__main__":
    main()
