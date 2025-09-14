#include <stdio.h>
#include <cs50.h>

// Function prototypes
void marioPyramid(int number);
int getNumber(void);

int main(void)
{
    int number = getNumber();
    marioPyramid(number);
    return 0;
}

// Will get a number between 1 and 8 from the user 
// and return it
int getNumber(void)
{
    int number;
    do
    {
        number = get_int("Type a number between 1 and 8\n");
    }
    while (number < 1 || number > 8);
    return number;
}

// Will print the Mario pyramid of the specified height
void marioPyramid(int number)
{
    int index;
    for (int i = 0; i < number; i++)
    {
        for (index = 0; index < number - i - 1; index++)
        {
            printf(" ");
        }
        for (index = 0; index <= i; index++)
        {
            printf("#");
        }
        printf("  ");
        for (index = 0; index <= i; index++)
        {
            printf("#");
        }
        printf("\n");
    }
}
