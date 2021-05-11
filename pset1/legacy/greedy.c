#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;

    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);

    int cents = (int) round(change * 100);
    int coin_count = 0;
    int coins[4] = {25, 10, 5, 1};
    int coin_value;

    for (int i = 0; i < 4; i++)
    {
        while (cents >= coins[i])
        {
            coin_count++;
            cents = cents - coins[i];
        }
    }

    printf("%i\n", coin_count);
}
