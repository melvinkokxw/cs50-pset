#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_alpha(string input_string);
int check_repeats(string input_string);
string convert_to_ciphertext(string plaintext, string cipher);

int main(int argc, string argv[])
{
    // Check if key is provided, and only one argument given
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check if key has 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Call function to check if only alphabets are present
    else if (check_alpha(argv[1]) == 0)
    {
        printf("Key must contain only alphabets.\n");
        return 1;
    }
    // Call function to check for repeats in key
    else if (check_repeats(argv[1]) == 0)
    {
        printf("Key must contain each letter exactly once.\n");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext: ");

        printf("ciphertext: %s\n", convert_to_ciphertext(plaintext, argv[1]));
    }

    return 0;
}

int check_alpha(string input_string)
{
    // Loop through string until null character
    for (int i = 0 ; input_string[i] != '\0' ; i++)
    {
        // If current character is not alphabet
        if (isalpha(input_string[i]) == 0)
        {
            return 0;
        }
    }

    // If all characters in string are alphabets
    return 1;
}

int check_repeats(string input_string)
{
    // Loop through plaintext string until null character
    for (int i = 0 ; input_string[i] != '\0' ; i++)
    {
        // Compare current character with the rest of the characters
        for (int j = i + 1 ; input_string[j] != '\0' ; j++)
        {
            // If current character match one of remaining characters, return 0
            if (input_string[i] == input_string[j])
            {
                return 0;
            }
        }
    }

    return 1;
}

string convert_to_ciphertext(string text, string cipher)
{
    int asciicode;

    // Loop through plaintext string until null character
    for (int i = 0 ; text[i] != '\0' ; i++)
    {
        if (isupper(text[i]) != 0)
        {
            asciicode = text[i];
            text[i] = toupper(cipher[asciicode - 65]);
        }
        else if (islower(text[i]) != 0)
        {
            asciicode = text[i];
            text[i] = tolower(cipher[asciicode - 97]);
        }
    }

    return text;
}
