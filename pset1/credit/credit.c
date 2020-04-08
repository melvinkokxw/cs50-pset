#include <stdio.h>
#include <cs50.h>
#include <math.h>

long long getCardNumber(void);
int getFirstSum(long long cardNumber);
int getSecondSum(long long cardNumber);
int validateSum(int firstSum, int secondSum);
string checkCardType(long long cardNumber);

int main(void)
{
    //get card number as input
    long long cardNumber = getCardNumber();

    //get sum of every other digit multiplied by 2
    int firstSum = getFirstSum(cardNumber);

    //get sum of remaining digits
    int secondSum = getSecondSum(cardNumber);

    //check if total sum is valid
    if (validateSum(firstSum, secondSum))
    {
        //get card type using function checkCardType
        printf("%s", checkCardType(cardNumber));
    }
    //if total sum is invalid
    else
    {
        printf("INVALID\n");
    }
}

long long getCardNumber(void)
{
    long long cardNumber;

    //get card number as input
    do
    {
        cardNumber = get_long_long("Number: ");
    }
    //check if input is positive number
    while (cardNumber < 0);

    return cardNumber;
}

int getFirstSum(long long cardNumber)
{
    cardNumber /= 10;

    int sum = 0;

    //cut the card number by 2 digits each loop
    for (int currentNumber; cardNumber > 0 ; cardNumber /= 100)
    {
        //get last digit of card number multiplied by 2
        currentNumber = cardNumber % 10 * 2;
        
        //add the individual digits of the previously evaluated number to the sum
        for (; currentNumber > 0 ; currentNumber /= 10)
        {
            sum += currentNumber % 10;
        }
    }

    return sum;
}

int getSecondSum(long long cardNumber)
{
    int sum = 0;

    //cut the card number by 2 digits each loop
    for (; cardNumber > 0 ; cardNumber /= 100)
    {
        //get last digit of current card number
        sum += cardNumber % 10;
    }

    return sum;
}

int validateSum(int firstSum, int secondSum)
{
    int totalSum = firstSum + secondSum;
    
    //check that total sum ends with 0
    return (totalSum % 10 == 0);
}

string checkCardType(long long cardNumber)
{
    //check if number is 15 digits and start with 34 or 37
    if (floor(cardNumber / pow(10, 13)) == 34 || floor(cardNumber / pow(10, 13)) == 37) 
    {
        return "AMEX\n";
    }
    //check if number is 16 digits and start with 51-55
    else if (floor(cardNumber / pow(10, 14)) >= 51 && floor(cardNumber / pow(10, 14)) <= 55)
    {
        return "MASTERCARD\n";
    }
    //check if number is 13 or 16 digits and start with 4
    else if (floor(cardNumber / pow(10, 12)) == 4 || floor(cardNumber / pow(10, 15)) == 4)
    {
        return "VISA\n";
    }
    //if fails all the above tests, not a valid card type
    else
    {
        return "INVALID\n";
    }
}
