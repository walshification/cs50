#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();

    for (int i = 0, l = strlen(name); i < l; ++i)
    {
        if (i == 0 || name[i - 1] == ' ')
        {
            printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
    return 0;
}
