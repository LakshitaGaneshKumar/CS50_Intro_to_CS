#include <stdio.h>
#include <cs50.h>

// this program prompts the user for their name and prints out "Hello, USER NAME."
int main(void)
{
    // prompts the user for their name and stores the result in the variable "name"
    string name = get_string("What is your name? ");

    // prints "Hello, USER NAME." to the screen
    printf("Hello, %s.\n", name);
}