#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

// Program that asks for a credit card number and decides which brand it is from or, if in any case, it's an invalid number
int main(void)
{
// Get card number from user. Must be positive.
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);

// Discard all numbers that have fewer digits than the card with fewer digits
    if (n < 1000000000000)
    {
        printf("INVALID\n");
        exit(0);
    }
// Discard all numbers that have more digits than the card with more digits, as there will surely be bigger numbers that can satisfy Luhn's algorithm
    if (n > 10000000000000000)
    {
        printf("INVALID\n");
        exit(0);
    }
// Get the last digit of the number
    long d1 = n % 10;
// Get the second to last digit. I will use two variables per digit to obtain to make writing the code easier and faster.
    long n2 = n % 100;
    long d2 = (n2 - d1) / 10;
// Get the next digit
    long n3 = n % 1000;
    long d3 = (n3 - n2) / 100;
// Next digit...
    long n4 = n % 10000;
    long d4 = (n4 - n3) / 1000;

    long n5 = n % 100000;
    long d5 = (n5 - n4) / 10000;

    long n6 = n % 1000000;
    long d6 = (n6 - n5) / 100000;

    long n7 = n % 10000000;
    long d7 = (n7 - n6) / 1000000;

    long n8 = n % 100000000;
    long d8 = (n8 - n7) / 10000000;

    long n9 = n % 1000000000;
    long d9 = (n9 - n8) / 100000000;

    long n10 = n % 10000000000;
    long d10 = (n10 - n9) / 1000000000;

    long n11 = n % 100000000000;
    long d11 = (n11 - n10) / 10000000000;

    long n12 = n % 1000000000000;
    long d12 = (n12 - n11) / 100000000000;

    long n13 = n % 10000000000000;
    long d13 = (n13 - n12) / 1000000000000;

// If this digits don't exist the variable will store 0. Since we'll add them later this has no effect.
    long n14 = n % 100000000000000;
    long d14 = (n14 - n13) / 10000000000000;

    long n15 = n % 1000000000000000;
    long d15 = (n15 - n14) / 100000000000000;

    long n16 = n % 10000000000000000;
    long d16 = (n16 - n15) / 1000000000000000;
// Multiply every other digit for checksum
    int d2_2 = d2 * 2;
    int d4_2 = d4 * 2;
    int d6_2 = d6 * 2;
    int d8_2 = d8 * 2;
    int d10_2 = d10 * 2;
    int d12_2 = d12 * 2;
    int d14_2 = d14 * 2;
    int d16_2 = d16 * 2;
// Get the digits of the products. Will attempt to get two digits in all cases. If there aren't two, it will come up as zero and then be summed without effect.
// This gets the second digit
    int d2_3 = d2_2 % 10;
// Substracting that to the original number and bringing it down one order of magnitud gets us the first digit.
    d2_2 = (d2_2 - d2_3) / 10;
// Will repeat process for every other digit.
    int d4_3 = d4_2 % 10;
    d4_2 = (d4_2 - d4_3) / 10;

    int d6_3 = d6_2 % 10;
    d6_2 = (d6_2 - d6_3) / 10;

    int d8_3 = d8_2 % 10;
    d8_2 = (d8_2 - d8_3) / 10;

    int d10_3 = d10_2 % 10;
    d10_2 = (d10_2 - d10_3) / 10;

    int d12_3 = d12_2 % 10;
    d12_2 = (d12_2 - d12_3) / 10;

    int d14_3 = d14_2 % 10;
    d14_2 = (d14_2 - d14_3) / 10;

    int d16_3 = d16_2 % 10;
    d16_2 = (d16_2 - d16_3) / 10;
// Addition of digits
    int check_sum = d2_2 + d2_3 + d4_2 + d4_3 + d6_2 + d6_3 + d8_2 + d8_3 + d10_2 + d10_3 + d12_2 + d12_3 + d14_2 + d14_3 + d16_2
                    + d16_3;
// Addition of all non-multiplied digits
    check_sum = check_sum + d1 + d3 + d5 + d7 + d9 + d11 + d13 + d15;
// Verify last digit is zero
    check_sum = check_sum % 10;
    if (check_sum == 0)
    {
// Determines if AMEX card by checking the first digits of a 15th digit card
        int c = 0;
        if ((d15 == 3 && d14 == 4) || (d15 == 3 && d14 == 7))
        {
            printf("AMEX\n");
            c = 1;
        }
// Determines if Mastercard card by checking the first digits of a 16th digit card
        if (d16 == 5 && ((d15 == 1) || (d15 == 2) || (d15 == 3) || (d15 == 4) || (d15 == 5)))
        {
            printf("MASTERCARD\n");
            c = 1;
        }
// Determines whether it's a Visa card
        if ((d13 == 4 && d15 == 0 && d16 == 0) || (d16 == 4))
        {
            printf("VISA\n");
            c = 1;
        }
        if (c == 0)
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

//Note to self, in case I want to change code to get digits using less variables: d3 = (d3 - d2 * 10 - d1) / 100;
}
