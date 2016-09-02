#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        printf("height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);

    int row = 0;
    while (height > 0)
    {
        for (int i = height - 1; i > 0; i--)
        {
            printf(" ");
        }
        for (int j = row + 2; j > 0; j--)
        {
            printf("#");
        }
        printf("\n");
        height--;
        row++;
    }
}
