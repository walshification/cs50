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

int linearSearch(int value, int values[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (value == values[i])
        {
            return value;
        }
    }

    // nothing found.
    return -1;
}

int binarySearch(int value, int values[], int min, int max)
{
    if (max < min)
    {
        return -1;
    }

    int middle = ((max - min) / 2) + min;

    if (value > values[middle])
    {
        min = middle + 1;
    }
    else
    {
        if (value < values[middle])
        {
            max = middle - 1;
        }
        else
        {
            return values[middle];
        }
    }
    return binarySearch(value, values, min, max);
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (value < 0)
    {
        return false;
    }

    int result = binarySearch(value, values, 0, n);

    return value == result;
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
