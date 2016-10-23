#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("What is the average length of your showers?\n");
    int water = GetInt();
    printf("minutes: %i\n", water);
    printf("bottles: %i\n", (water * 12));
}
