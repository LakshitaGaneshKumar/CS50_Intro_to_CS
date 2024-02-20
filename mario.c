#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declares the variable "height"
    int height;

    // prompts the user to input a number between 1 and 8
    // the user is reprompted if the input any other number
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // declares variables i, j, and k
    int i;
    int j;
    int k;

    // prints a pyramid to the screen that has a height and width of the inputed number
    for (i = 0; i < height; i++)
    {
        // prints a certain number of spaces on each line so the pyramid is configured towards the right-hand side
        for (j = height - (i + 2); j >= 0; j--)
        {
            printf(" ");
        }

        // prints the "blocks" of the pyramid for each line
        for (k = 1; k <= (i + 1); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}