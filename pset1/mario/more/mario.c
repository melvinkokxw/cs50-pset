#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    //ask for height input and ensures it is within 1-8
    do 
    {
        height = get_int("what height should the wall be?\n");
    } 
    while (height < 1 || height > 8);

    for (int i = 0 ; i < height ; i++)
    {
        //create left side of wall
        //create blank spaces for indentation
        for (int j = 0 ; j < height - i - 1 ; j++) 
        {
            printf(" ");
        }
        //create hashes
        for (int k = 0 ; k <= i ; k++)
        {
            printf("#");
        }

        printf("  "); // wall gap

        //create right side of wall
        //create hashes
        for (int k = 0 ; k <= i ; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}
