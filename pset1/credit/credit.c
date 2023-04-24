#include <cs50.h>
#include <stdio.h>

// future Nando hi i'm you but in the past, next comments was translated by google
int main(void)
{

    // power of 10
    long cc = 1;
    // define checksum
    int checksum;
    // define cardnum modulo 10
    long card;
    // count=
    int i = 0;
    // from right to left odd number
    int odd = 0;
    // from right to left pair number
    int pair = 0;
    // remainder
    int remainder;
    // immutable card number
    long realcard;
    do
    {
        // prompt credit number
        realcard = get_long("Number: ");
    }
    // if cardnumer is integer
    while (realcard < 1);
    // safe cardnumber
    card = realcard;
    // if cardnumber modulo 10
    while (card > 0)
    {

        // power of 10 +1
        cc *= 10;
        i += 1;
        // if count is pair
        if (i % 2 == 0)
        {
            // remainder 10 multiply by 2
            remainder = 2 * (card % 10);
            // first digit of remainder
            pair += remainder / 10;
            // second
            pair += remainder % 10;

        }
        else
        {
            // remainder 10
            remainder = card % 10;
            // add to odd
            odd += remainder;
        }
        // delete last number from card
        card = card / 10;


    }

    checksum = odd + pair;

    // bussines ruler from visa, first number 4 and digits between 13 - 16
    if (realcard / (cc / 10) == 4 && checksum % 10 == 0 && i >= 13 && i <= 16)
    {
        printf("VISA\n");
    }
    // bussines ruler from MC, first number between 51 - 55 and digits  16
    else if (checksum % 10 == 0 && i == 16 && realcard / (cc / 100) > 50 && realcard / (cc / 100) < 56)
    {
        printf("MASTERCARD\n");
    }
    // bussines ruler from AMEX, first number 34 or 37  and digits 15
    else if (checksum % 10 == 0 && i == 15 && (realcard / (cc / 100) == 34 || realcard / (cc / 100) == 37))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}