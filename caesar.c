#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int only_digits(string command);
void rotate(string plaintext, int key);

int main(int argc, string argv[])
{
    // the program runs if there are only two command line arguments, including the name of the program
    // else, int main returns 1 and exits the program
    if (argc == 2)
    {
        // the key is assigned to the command string
        string command = argv[1];

        // checks if there are only digits in the key
        int x = only_digits(command);

        // returns the result of the only_digits function
        // if x = 0, the key is only digits, main returns 0, and the program continues to run
        if (x == 0)
        {
            // prompts user for the plaintext
            string plaintext = get_string("plaintext: ");

            // creates the ciphertext
            rotate(plaintext, atoi(argv[1]));

            return 0;
        }
        // if x is not 0, the key is not only digits, main returns 1, and the program stops with an error message
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    }
    // the program stops if the user imputs more than two command line arguments, including the name of the program
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

int only_digits(string command)
{
    int length = strlen(command);
    int x;

    // checks the command to see if it's only digits or not
    for (int i = 0; i < length; i++)
    {
        // if the command is only digits, only_digits returns 0 and the program continues to run
        if (isdigit(command[i]))
        {
            x = 0;
        }
        // if the command is not only digits, only_digits returns 1, which stops the program
        else
        {
            x = 1;
        }
    }
    return x;
}

void rotate(string plaintext, int key)
{
    // finds length of the plaintext
    int plaintext_length = strlen(plaintext);
    printf("ciphertext: ");

    // sets the key to a number between 0 - 26
    key = key % 26;

    // rotates the plaintext based on the key to create the ciphertext
    for (int j = 0; j < plaintext_length; j++)
    {
        if (isupper(plaintext[j]))
        {
            printf("%c", (((plaintext[j] - 65) + key) % 26) + 65);
        }
        else if (islower(plaintext[j]))
        {
            printf("%c", (((plaintext[j] - 97) + key) % 26) + 97);
        }
        else
        {
            printf("%c", plaintext[j]);
        }
    }

    printf("\n");
}