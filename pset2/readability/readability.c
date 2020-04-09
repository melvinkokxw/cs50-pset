#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string input_text);
int count_words(string input_text);
int count_sentences(string input_text);
int get_index(int letters, int words, int sentences);

int main(void)
{
    string input_text = get_string("Text: ");

    //call function to count number of letters in string
    int letters = count_letters(input_text);

    //call function to count number of words in string
    int words = count_words(input_text);

    //call function to count number of sentences in string
    int sentences = count_sentences(input_text);

    //call function to get Coleman-Liau index of input text
    int index = get_index(letters, words, sentences);

    //if index is between 1-15
    if (index >= 1 && index <= 15)
    {
        printf("Grade %i\n", index);
    }

    //if index is less than 1
    else if (index <= 1)
    {
        printf("Before Grade 1\n");
    }

    //if index is greater than 15 (16+)
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string input_text)
{
    int letters = 0;

    //loop through string until null character is reached
    for (int i = 0; input_text[i] != '\0' ; i++)
    {
        //if current character is a alphabet
        if (isalpha(input_text[i]) != 0)
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string input_text)
{
    int words = 0;

    //loop through string until null character is reached
    for (int i = 0; input_text[i] != '\0' ; i++)
    {
        //if current character is a space, it marks the end of a word
        if (input_text[i] == ' ')
        {
            words++;
        }
    }

    //increse word count by one due to word at end of sentence that isn't followed by a space
    return ++words;
}

int count_sentences(string input_text)
{
    int sentences = 0;

    //loop through string until null character is reached
    for (int i = 0; input_text[i] != '\0' ; i++)
    {
        //assume if current character is '.', '!' or '?' it marks the end of a sentence
        if (input_text[i] == '.' || input_text[i] == '!' || input_text[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}

int get_index(int letters, int words, int sentences)
{
    float l = letters / (float)words * 100;
    float s = sentences / (float)words * 100;

    int index =  round(0.0588 * l - 0.296 * s - 15.8);

    return index;
}
