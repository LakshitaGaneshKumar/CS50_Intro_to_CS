#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declares the variables i, last_digit, and second_last_digit;
    int i;
    int last_digit;
    int second_last_digit;

    // declares and assigns the variables sum1, sum2, divider, and divider2
    int sum1 = 0;
    int sum2 = 0;
    int divider = 100;
    int divider2 = 10;

    // prompts user for card number
    long card_number = get_long("Card Number: ");

    // calculates length of card number
    int length = 0;
    long cc = card_number;
    while (cc > 0)
    {
        cc = cc / 10;
        length++;
    }
    // reassigns the cc value to be the card number for later usage
    cc = card_number;

    // checks if the user inputed a possible card number length or not
    // if the length of the card number is not 13, 15, or 16 digits, the program outputs "INVALID" to state that the inputed card number is invalid
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID");
    }

    // else, if the the card number is a length of 13, 15, or 16 digits, the program calculates the validity of the card number
    else
    {
        // the for loop finds the digits in every other place in the card number, starting from the second to last digit
        for (i = 0; i <= length; i++)
        {
            // finds the last digit, removes it, and adds it to sum1
            last_digit = cc % 10;
            cc = cc / 10;
            sum1 = sum1 + last_digit;

            // finds the second to last digit, removes it, multiplies it by 2, and adds it to sum2 if it's less than 10 after multiplication
            // else, the two-digit number is split into two one-digit numbers, which are then multiplied by 2 and added to sum2
            second_last_digit = cc % 10;
            cc = cc / 10;

            if ((second_last_digit * 2) < 10)
            {
                sum2 = sum2 + (second_last_digit * 2);
            }
            else
            {
                sum2 = sum2 + ((second_last_digit % 10) * 2) + ((((second_last_digit % 100) - (second_last_digit % 10)) / 10) * 2);
            }
        }
    }

    printf("Length: %i\n", length);
    printf("Sum1: %i\n", sum1);
    printf("Sum2: %i\n", sum2);
}