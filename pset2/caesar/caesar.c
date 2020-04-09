#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int is_number(string input);
string caesar_cipher(string plaintext, string cipher);

int main(int argc, string argv[])
{
    //check if exactly one argument is provided
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //call function to check if argument is a number
    else if (is_number(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //if one argument provided and argument is number
    else
    {
        printf("success\n");
        printf("%s\n", argv[1]);

        //get plaintext input
        string plaintext = get_string("plaintext: ");

        //call function to convert plaintext to ciphertext
        string ciphertext = caesar_cipher(plaintext, argv[1]);

        printf("ciphertext: %s\n", ciphertext);
    }
}

//function checks if input string is a number
int is_number(string input)
{
    //loop through string until null character
    for (int i = 0 ; input[i] != '\0' ; i++)
    {
        //if current character is not a digit, return 0
        if (isdigit(input[i]) == 0)
        {
            return 0;
        }
    }

    //all characters are digits, return 1
    return 1;
}

string caesar_cipher(string plaintext, string cipher)
{
    int asciicode;

    //loop through string until null character
    for (int i = 0 ; plaintext[i] != '\0' ; i++)
    {
        //if current character is uppercase character
        if (isupper(plaintext[i]) != 0)
        {
            //get character's to its ascii code
            asciicode = plaintext[i];

            //add cipher key to ascii code and wraps if necessary
            plaintext[i] = ((asciicode - 65 + atoi(cipher)) % 26 + 65);
        }
        //if current character is lowercase character
        else if (islower(plaintext[i]) != 0)
        {
            //get character's to its ascii code
            asciicode = plaintext[i];

            //add cipher key to ascii code and wraps if necessary
            plaintext[i] = ((asciicode - 97 + atoi(cipher)) % 26 + 97);
        }
    }

    return plaintext;
}
