#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // declares the variable "cents"
    int cents;

    // prompts the user to input the amount of change owed in cents
    // the user is reprompted if the inputed number is negative
    do
    {
        cents = get_int("Change Owed: ");
    }
    while (cents < 0);

    return cents;
}

int calculate_quarters(int cents)
{
    // declares the variable "quarters"
    int quarters;

    // calculates the number of quarters that are owed to the customer
    if (cents / 25 == 1)
    {
        quarters = 1;
    }
    else if (cents / 25 > 1)
    {
        quarters = (cents / 25) - ((cents % 25) / 25);
    }
    else
    {
        quarters = 0;
    }

    // returns the number of quarters owed
    return quarters;
}

int calculate_dimes(int cents)
{
    // declares the variable "dimes"
    int dimes;

    // calculates the number of dimes owed
    if (cents / 10 == 1)
    {
        dimes = 1;
    }
    else if (cents / 10 > 1)
    {
        dimes = (cents / 10) - ((cents % 10) / 10);
    }
    else
    {
        dimes = 0;
    }

    // returns the number of dimes owed
    return dimes;
}

int calculate_nickels(int cents)
{
    // declares the variable "nickels"
    int nickels;

    // calculates the number of nickles owed
    if (cents / 5 == 1)
    {
        nickels = 1;
    }
    else if (cents / 5 > 1)
    {
        nickels = (cents / 5) - ((cents % 5) / 5);
    }
    else
    {
        nickels = 0;
    }

    // returns the number of nickels owed
    return nickels;
}

int calculate_pennies(int cents)
{
    // declares the variable "pennies"
    int pennies;

    // returns cents for the number of pennies
    return pennies = cents;
}
