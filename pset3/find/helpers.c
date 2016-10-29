/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (value < 0)
    {
        return false;
    }

    // Linear search
    for (int i = 0; i < n; ++i)
    {
        if (value == values[i])
        {
            return true;
        }
    }

    // nothing found.
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // bubble sort
    bool unchanged = true;
    int unsorted_length = n - 1;

    for (int i = 0, worst_case = unsorted_length; i < worst_case; ++i)
    {
        unchanged = true;

        for (int j = 0; j < unsorted_length; ++j)
        {
            int initial = values[j];
            int next = values[j + 1];

            if (initial > next)
            {
                values[j] = next;
                values[j + 1] = initial;
                unchanged = false;  // values changed position!
            }
        }

        if (unchanged)
        {
            // not changing any value positions means they're sorted
            return;
        }
        // We can trust the last value is sorted
        --unsorted_length;
    }
    return;
}
