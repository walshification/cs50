#include <cs50.h>
#include <stdio.h>

/*
To be compiled in the cs50 IDE. Sign in with your GitHub account at:

https://ide.cs50.io/

Challenge:

Say we have a population of n llamas. Each year, n / 3 new llamas are
born, and n / 4 llamas pass away.

Determine how long it takes for a population to reach a particular size.
*/

int main(void)
{
    // Prompt for start size
    int start = 0;
    while (start < 9)
    {
        start = get_int("Start size: ");
    }

    // Prompt for end size
    int end = 0;
    while (end < start)
    {
        end = get_int("End size: ");
    }

    // Calculate number of years until we reach threshold
    int pop = start;
    int years = 0;
    while (pop < end)
    {
        years++;
        pop += (pop / 3) - pop / 4;
    }

    // Print number of years
    printf("Years: %i\n", years);
}