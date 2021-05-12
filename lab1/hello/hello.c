#include <cs50.h>
#include <stdio.h>

/*
To be compiled in the cs50 IDE. Sign in with your GitHub account at:

https://ide.cs50.io/

Challenge:

Modify this program in such a way that it first prompts the user for
their name and then prints hello, so-and-so, where so-and-so is their
actual name.
*/

// I'm a function that doesn't return anything!
int main(void)
{
    // Gnab the user's name.
    string name = get_string("What is your name?\n");
    // Print away!
    printf("hello, %s\n", name);
}