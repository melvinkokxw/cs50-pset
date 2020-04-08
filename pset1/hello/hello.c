#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get user input for their name
    string name = get_string("what is your name?\n");

    //prints a personalised greeting
    printf("hello, %s\n", name);
}
