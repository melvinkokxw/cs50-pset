#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) 
{
    float dollars;

    //get user input, ensures input is positive
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    //convert user input to cents in int type for accuracy
    int cents = round(dollars * 100);

    //declare counter
    int i;

    //count number of coins required to bring cents to 0
    for (i = 0 ; cents > 0 ; i++)
    {
        if (cents >= 25)
        {
            cents -= 25;
        } 
        else if (cents >= 10)
        {
            cents -= 10;
        } 
        else if (cents >= 5)
        {
            cents -= 5;
        } 
        else if (cents >= 1)
        {
            cents -= 1;
        }
    }

    //prints number of coins needed
    printf("%i\n", i);
}
