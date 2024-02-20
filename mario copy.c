#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declares the variable height
    int height;

    // prompts the user to input a value between 1 and 8 for the height of the pyramid
    // the user is reprompted if the inputed value is any other number
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // declares variables i, j, k, n, m
    int i;
    int j;
    int k;
    int n;

    for (i = 0; i < height; i++)
    {
        // prints a certain number of spaces before the first pyramid so it's faces the left side of the screen
        for (j = height - (i + 2); j >= 0; j--)
        {
            printf(" ");
        }

        // prints the "bricks" for the first pyramid
        for (k = 1; k <= (i + 1); k++)
        {
            printf("#");
        }

        // prints a space on each line between the two pyramids
        printf("  ");

        // prints the second pyramid
        for (n = 1; n <= (i + 1); n++)
        {
            printf("#");
        }

        // enters a new line to create a new row for the pyramid
        printf("\n");
    }

}